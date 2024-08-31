#include "Component_PlayerBehavior.h"

// インクルード
#include "../../../../../Engine/Collider/BoxCollider.h"
#include "../../../../../Engine/Collider/SphereCollider.h"
#include "../../../../../Engine/DirectX/Direct3D.h"
#include "../../../../../Engine/DirectX/Input.h"
#include "../../../../../Engine/GameObject/Camera.h"
#include <directxmath.h> 
#include "../../Stage.h"
#include "../../StageObject.h"
#include "../../SkySphere.h"
#include "../AttackComponents/Component_MeleeAttack.h"
#include "../AttackComponents/Component_ShootAttack.h"
#include "../GaugeComponents/Component_HealthGauge.h"
#include "../MoveComponents/Component_WASDInputMove.h"
#include "../TimerComponent/Component_Timer.h"
#include "../MotionComponent/Component_PlayerMotion.h"
#include <algorithm> 
#include "../../../../../Game/Objects/Stage/Components/GaugeComponents/Component_HealthGauge.h"
#include "../../../../../Engine/ImGui/imgui.h"
#include "../MoveComponents/Component_TackleMove.h"
#include "../../../UI/CountDown.h"
#include "../../../Camera/TPSCamera.h"

namespace {
    const int SHOOT_FRAME = 115;

    bool IsXMVectorZero(XMVECTOR _vec) {
		return XMVector3Equal(_vec, XMVectorZero());
	}

    bool IsWASDKey() {
		return Input::IsKey(DIK_W) || Input::IsKey(DIK_A) || Input::IsKey(DIK_S) || Input::IsKey(DIK_D);
	}
}




struct CompareDist {
    bool operator()(const RayCastData& lhs, const RayCastData& rhs) const {
        return lhs.dist < rhs.dist;
    }
};

using namespace DirectX;
Component_PlayerBehavior::Component_PlayerBehavior(string _name, StageObject* _holder, Component* _parent)
    : Component(_holder, _name, PlayerBehavior, _parent)
{
}

void Component_PlayerBehavior::Initialize()
{

    // コライダーの追加
    holder_->AddCollider(new BoxCollider(XMFLOAT3(0, 0, 0), XMFLOAT3(1, 1, 1)));

    holder_->SetScale(XMFLOAT3(0.5f, 0.5f, 0.5f));

    // 子コンポーネントの追加
    if (FindChildComponent("InputMove") == false)AddChildComponent(CreateComponent("InputMove", WASDInputMove, holder_, this));
    if (FindChildComponent("MeleeAttack") == false)AddChildComponent(CreateComponent("MeleeAttack", MeleeAttack, holder_, this));
    if (FindChildComponent("ShootAttack") == false)AddChildComponent(CreateComponent("ShootAttack", ShootAttack, holder_, this));
    if (FindChildComponent("Timer") == false)AddChildComponent(CreateComponent("Timer", Timer, holder_, this));
    if (FindChildComponent("HealthGauge") == false)AddChildComponent(CreateComponent("PlayerHealthGauge", HealthGauge, holder_, this));
    if (FindChildComponent("PlayerMotion") == false)AddChildComponent(CreateComponent("PlayerMotion", PlayerMotion, holder_, this));
    if (FindChildComponent("TackleMove") == false)AddChildComponent(CreateComponent("TackleMove", TackleMove, holder_, this));
}

void Component_PlayerBehavior::Update()
{

    static bool isGameStart = false;
    // ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
    // カウント制御されている場合の処理
    // ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
    CountDown* countDown = (CountDown*)(holder_->FindObject("CountDown"));
    if (countDown != nullptr && isGameStart == false) {

        // 移動コンポーネントの取得 & 有無の確認
        Component_WASDInputMove* move = (Component_WASDInputMove*)(GetChildComponent("InputMove"));
        if (GetChildComponent("InputMove") == nullptr)return;

        // カウントダウンが終了した場合
        if (countDown->IsFinished()) {

            //移動を可能にする
            move->Execute();

            // ゲームスタートフラグを立てる
            isGameStart = true;
        }
        else {
            // 移動を不可能にする
            move->Stop();
        }
    }
    

    // ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
    // 状態ごとの処理
    // ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
    switch (nowState)
    {
    case PSTATE_IDLE:           Idle();         break;  // 現在の状態がIDLEの場合
    case PSTATE_WALK:           Walk();         break;  // 現在の状態がWALKの場合
    case PSTATE_SHOOT:          Shoot();        break;  // 現在の状態がSHOOTの場合
    case PSTATE_DASH:           Dash();         break;  // 現在の状態がDASHの場合
    }
}

void Component_PlayerBehavior::Release()
{
}

void Component_PlayerBehavior::DrawData()
{
    ImGui::Text("%f,%f,%f,%f", frontVec_.m128_f32);
    auto timer = dynamic_cast<Component_Timer*>(GetChildComponent("Timer"));
    if (timer == nullptr)return;
    ImGui::Text("%f", timer->GetNowTime());

    if (ImGui::Button("Idle")) SetState(PSTATE_IDLE);
    if (ImGui::Button("Walk")) SetState(PSTATE_WALK);
    if (ImGui::Button("Shoot")) SetState(PSTATE_SHOOT);

}

void Component_PlayerBehavior::Idle()
{
    // 移動コンポーネントの取得 & 有無の確認
    Component_WASDInputMove* move = (Component_WASDInputMove*)(GetChildComponent("InputMove"));
    if (move == nullptr)return;

    // 状態優先度：歩行 > 射撃
    // `InputMove`コンポーネントの移動フラグが立っていたら...歩行状態に遷移
    if (move->IsMove()) SetState(PSTATE_WALK);

    // マウスの左ボタンが押されていたかつ、マウスの右ボタンが押されてたら、射撃状態に遷移
    else if (Input::IsMouseButtonDown(0)) SetState(PSTATE_SHOOT);

    // スペースキーが押されていたら...ダッシュ状態に遷移
    else if (Input::IsKeyDown(DIK_SPACE)) SetState(PSTATE_DASH);
}

void Component_PlayerBehavior::Walk()
{
    // 移動コンポーネントの取得 & 有無の確認
    Component_WASDInputMove* move = (Component_WASDInputMove*)(GetChildComponent("InputMove"));
    if (move == nullptr)return;

    // 移動コンポーネントが移動していなかったら...IDLE状態に遷移
    if (move->IsMove() == false) {
        SetState(PSTATE_IDLE);
        return; // ここで処理を終了
    }

    // 状態優先度：ダッシュ > 射撃
    // スペースキーが押されていたら...ダッシュ状態に遷移
    if (Input::IsKeyDown(DIK_SPACE)) SetState(PSTATE_DASH);

    // マウスの左ボタンが押されていたかつ、マウスの右ボタンが押されてたら、射撃状態に遷移
    else if(Input::IsMouseButtonDown(0)) SetState(PSTATE_SHOOT);
}

void Component_PlayerBehavior::Shoot()
{
    // モーションコンポーネントの取得 & 有無の確認
    Component_PlayerMotion* motion = (Component_PlayerMotion*)(GetChildComponent("PlayerMotion"));
    if (motion == nullptr)return;

    // TPSカメラの方向を取得
    TPSCamera* tpsCamera = (TPSCamera*)holder_->FindObject("TPSCamera");
    if(tpsCamera != nullptr)holder_->SetRotateY(tpsCamera->GetAngle().y);

    // 射撃モーションのアニメーションの現在の再生時間を取得
    float nowFrame = motion->GetNowFrame();

    // NOTE: 一度だけ射撃処理を実行するためのフラグ
    static bool isShoot = false;

    // 現在のフレームが射撃アニメーションのちょうどいいタイミングを過ぎたら...
    if (nowFrame >= SHOOT_FRAME && isShoot == false) {

        // 発射オプションを設定
        Component_ShootAttack* shoot = (Component_ShootAttack*)(GetChildComponent("ShootAttack"));
        {
            // 射撃コンポーネントの有無の確認
            if (shoot == nullptr)return;

            // 発射位置を設定
            XMFLOAT3 shootPosition = holder_->GetPosition();
            shootPosition.y += shootHeight_;
            shoot->SetShootingPosition(shootPosition);

            // 発射方向を設定
            shoot->SetShootingDirection(CalcShootDirection());

            // 発射速度を設定
            shoot->SetShootingSpeed(2.f);
        }

        // 射撃処理を実行
        shoot->Execute();

        // 射撃フラグを立てる
        isShoot = true;
    }

    // 移動コンポーネントの取得 & 有無の確認
    Component_WASDInputMove* move = (Component_WASDInputMove*)(GetChildComponent("InputMove"));
    if (move != nullptr) move->Stop();


    // NOTE: 終了するためのフラグ
    bool isEnd = false;

    // スペースキーが押されていたら...ダッシュ状態に遷移
    if (Input::IsKeyDown(DIK_SPACE)) { isEnd = true; SetState(PSTATE_DASH); }

    // アニメーションが終わったら...
    if (motion->IsEnd()) { isEnd = true; SetState(PSTATE_IDLE); }

    if(isEnd == true){
        // 射撃フラグをリセット
        isShoot = false;

        // 移動コンポーネントの再開
        if (move != nullptr) move->Execute();
    }
}

void Component_PlayerBehavior::Dash()
{
    // NOTE: 一度だけダッシュ処理を実行するためのフラグ
    static bool isDash = false;
    
    // 移動コンポーネントの取得 & 有無の確認
    Component_WASDInputMove * move = (Component_WASDInputMove*)(GetChildComponent("InputMove"));
    if (move == nullptr)return;

    // 突進コンポーネントの取得 & 有無の確認
    Component_TackleMove* tackle = (Component_TackleMove*)(GetChildComponent("TackleMove"));
    if (tackle != nullptr && isDash == false) {

        // 突進方向を設定
        XMVECTOR dir{ 0,0,-1,0 }; {
            // 移動を不可能にする
            move->Stop();

            // 移動方向がゼロベクトルでなければ、移動方向を取得
            if (IsXMVectorZero(move->GetMoveDirection()) == false)dir = move->GetMoveDirection();
        }
		tackle->SetDirection(dir);

		// 突進距離を設定
		tackle->SetDistance(5.f);

		// 突進処理を実行
		tackle->Execute();

        // ダッシュフラグを立てる
        isDash = true;
    }

    // 突進処理が終了していたら...
    if (tackle->IsActived() == false) {

        // ダッシュフラグをリセット
		isDash = false;

        //移動を可能にする
        move->Execute();

        // 状態を遷移
        IsWASDKey() ? SetState(PSTATE_WALK) : SetState(PSTATE_IDLE);
    }
}

bool Component_PlayerBehavior::IsDead()
{
    auto hg = dynamic_cast<Component_HealthGauge*>(GetChildComponent("PlayerHealthGauge"));
    if (hg == nullptr)return false;

    return hg->IsDead();
}

XMVECTOR Component_PlayerBehavior::CalcShootDirection()
{
    // ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
    // 必要情報の取得
    // ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝

    // レイキャストデータを作成
    RayCastData data; {
        // レイの発射位置 NOTE: ワールド座標系でのカメラの位置
        data.start = Camera::GetPosition();

        // レイの方向 NOTE: カメラの視線ベクトルを正規化したもの,座標系に依存しないものと考える
        XMStoreFloat3(&data.dir, XMVector3Normalize(Camera::GetSightLine()));
    }

    // ヒットしたレイキャストデータを格納するリストを用意
    vector<RayCastData> hitRayCastDatalist;

    // ステージオブジェクトの取得
    Stage* pStage = ((Stage*)holder_->FindObject("Stage"));
    vector<StageObject*> objects = pStage != nullptr ? pStage->GetStageObjects() : vector<StageObject*>();

    for (auto obj : objects) {

        // 自分自身のオブジェクトだったらスキップ
        if (obj->GetObjectName() == holder_->GetObjectName()) continue;

        // レイキャストを実行
        Model::RayCast(obj->GetModelHandle(), &data);

        // レイが当たったら
        if (data.hit) {

            // レイキャストが当たった位置をワールド座標系に変換
            XMStoreFloat3(&data.pos, XMVector3TransformCoord(XMLoadFloat3(&data.pos), obj->GetWorldMatrix()));

            // レイキャストデータをリストに追加
            hitRayCastDatalist.push_back(data);
        }
    }

    // レイキャストデータリストが空でなければ
    if (hitRayCastDatalist.empty() == false) {

        // 配列の中身を比較して最も近いものを取得
        // プレイヤーの位置からの距離を計算し、shootDirに代入
        auto min_iter = std::min_element(rayHitObjectList_.begin(), rayHitObjectList_.end(), CompareDist());

        // イテレータが有効か確認して最小要素の dist を出力
        if (min_iter != rayHitObjectList_.end()) {
            XMFLOAT3 holderPos = holder_->GetPosition();
            return XMVector3Normalize(XMLoadFloat3(&min_iter->pos) - XMLoadFloat3(&holderPos));
        }
    }

    // レイキャストデータリストが空だったら
    return Camera::GetSightLine();
}
