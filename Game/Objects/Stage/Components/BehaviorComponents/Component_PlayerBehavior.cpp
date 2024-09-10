﻿#include "Component_PlayerBehavior.h"

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
#include "../../../../../Engine/SceneManager.h"
#include "../../../Game/Objects/UI/UIProgressBar.h"
#include "../../../Game/Objects/UI/UIPanel.h"
#include "../../../UI/UIImage.h"

namespace {
    const int SHOOT_FRAME = 115;

    bool IsXMVectorZero(XMVECTOR _vec) {
		return XMVector3Equal(_vec, XMVectorZero());
	}

    bool IsWASDKey() {
		return Input::IsKey(DIK_W) || Input::IsKey(DIK_A) || Input::IsKey(DIK_S) || Input::IsKey(DIK_D);
	}

    struct CompareDist {
        bool operator()(const RayCastData& lhs, const RayCastData& rhs) const {
            return lhs.dist < rhs.dist;
        }
    };

}

Component_PlayerBehavior::Component_PlayerBehavior(string _name, StageObject* _holder, Component* _parent)
    : Component(_holder, _name, PlayerBehavior, _parent)
    , shootHeight_(1.0f), isGameStart_(false), nowState_(PLAYER_STATE_IDLE), prevState_(PLAYER_STATE_IDLE)
{
}

void Component_PlayerBehavior::Initialize()
{
    // コライダーの追加
    holder_->AddCollider(new BoxCollider(XMFLOAT3(0, 0, 0), XMFLOAT3(1, 1, 1)));

    // effekseer: :Effectの読み込み
    EFFEKSEERLIB::gEfk->AddEffect("shield", "Effects/Undine13.efk");/*★★★*/

    // 子コンポーネントの追加
    if (FindChildComponent("InputMove") == false)AddChildComponent(CreateComponent("InputMove", WASDInputMove, holder_, this));
    if (FindChildComponent("ShootAttack") == false)AddChildComponent(CreateComponent("ShootAttack", ShootAttack, holder_, this));
    if (FindChildComponent("PlayerHealthGauge") == false)AddChildComponent(CreateComponent("PlayerHealthGauge", HealthGauge, holder_, this));
    if (FindChildComponent("PlayerMotion") == false)AddChildComponent(CreateComponent("PlayerMotion", PlayerMotion, holder_, this));
    if (FindChildComponent("TackleMove") == false)AddChildComponent(CreateComponent("TackleMove", TackleMove, holder_, this));


}

void Component_PlayerBehavior::Update()

{
    // ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
    // カウント制御されている場合の処理
    // ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
    CountDown* countDown = (CountDown*)(holder_->FindObject("CountDown"));
    if (countDown != nullptr && isGameStart_ == false) {

        // 移動コンポーネントの取得 & 有無の確認
        Component_WASDInputMove* move = (Component_WASDInputMove*)(GetChildComponent("InputMove"));
        if (GetChildComponent("InputMove") == nullptr)return;

        // カウントダウンが終了した場合
        if (countDown->IsFinished()) {

            //移動を可能にする
            move->Execute();

            // ゲームスタートフラグを立てる
            isGameStart_ = true;
        }
        else {
            // 移動を不可能にする
            move->Stop();
            return;
        }
    }
    
    // HP関連処理
    {
		// プレイヤーのHPゲージコンポーネントを取得
		Component_HealthGauge* hg = (Component_HealthGauge*)(GetChildComponent("PlayerHealthGauge"));

		// UIProgressBarを取得
		UIProgressBar* hpBar = (UIProgressBar*)UIPanel::GetInstance()->FindObject("playerHPBar");

		// HPバーの値を設定
		if (hpBar != nullptr && hg != nullptr)hpBar->SetProgress(&hg->now_, &hg->max_);

        // HPが0以下になったら... DEAD状態に遷移
        if (hg != nullptr)if (hg->IsDead() == true)SetState(PLAYER_STATE_DEAD);
    }

    // ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
    // 状態ごとの処理
    // ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
    switch (nowState_)
    {
    case PLAYER_STATE_IDLE:           Idle();         break;  // 現在の状態がIDLEの場合
    case PLAYER_STATE_WALK:           Walk();         break;  // 現在の状態がWALKの場合
    case PLAYER_STATE_SHOOT:          Shoot();        break;  // 現在の状態がSHOOTの場合
    case PLAYER_STATE_DODGE:          Dodge();         break;  // 現在の状態がDASHの場合
    case PLAYER_STATE_DEAD:            Dead();         break;  // 現在の状態がDEADの場合
    }
}

void Component_PlayerBehavior::Release()
{
}

void Component_PlayerBehavior::Save(json& _saveObj)
{
	_saveObj["shootHeight"] = shootHeight_;

    _saveObj["InvincibilityFrame"] = InvincibilityFrame_;
}

void Component_PlayerBehavior::Load(json& _loadObj)
{
    if (_loadObj.contains("shootHeight"))shootHeight_ = _loadObj["shootHeight"];

    if (_loadObj.contains("InvincibilityFrame"))InvincibilityFrame_ = _loadObj["InvincibilityFrame"];
}

void Component_PlayerBehavior::DrawData()
{
    // 高さの設定
    ImGui::DragFloat("ShootHeight", &shootHeight_, 0.1f);

    // 無敵フレームの設定
    ImGui::DragInt("InvincibilityFrame", &InvincibilityFrame_, 1);
}

void Component_PlayerBehavior::Idle()
{
    // 移動コンポーネントの取得 & 有無の確認
    Component_WASDInputMove* move = (Component_WASDInputMove*)(GetChildComponent("InputMove"));
    if (move == nullptr)return;

    // 状態優先度：歩行 > 射撃
    // `InputMove`コンポーネントの移動フラグが立っていたら...歩行状態に遷移
    if (move->IsMove()) SetState(PLAYER_STATE_WALK);

    // マウスの左ボタンが押されていたかつ、マウスの右ボタンが押されてたら、射撃状態に遷移
    else if (Input::IsMouseButtonDown(0)) SetState(PLAYER_STATE_SHOOT);

    // スペースキーが押されていたら...ダッシュ状態に遷移
    else if (Input::IsKeyDown(DIK_SPACE)) SetState(PLAYER_STATE_DODGE);
}

void Component_PlayerBehavior::Walk()
{
    // 移動コンポーネントの取得 & 有無の確認
    Component_WASDInputMove* move = (Component_WASDInputMove*)(GetChildComponent("InputMove"));
    if (move == nullptr)return;

    // 移動コンポーネントが移動していなかったら...IDLE状態に遷移
    if (move->IsMove() == false) {
        SetState(PLAYER_STATE_IDLE);
        return; // ここで処理を終了
    }

    // 状態優先度：ダッシュ > 射撃
    // スペースキーが押されていたら...ダッシュ状態に遷移
    if (Input::IsKeyDown(DIK_SPACE)) SetState(PLAYER_STATE_DODGE);

    // マウスの左ボタンが押されていたかつ、マウスの右ボタンが押されてたら、射撃状態に遷移
    else if(Input::IsMouseButtonDown(0)) SetState(PLAYER_STATE_SHOOT);
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
    if (Input::IsKeyDown(DIK_SPACE)) { isEnd = true; SetState(PLAYER_STATE_DODGE); }

    // アニメーションが終わったら...
    if (motion->IsEnd()) { isEnd = true; SetState(PLAYER_STATE_IDLE); }

    if(isEnd == true){
        // 射撃フラグをリセット
        isShoot = false;

        // 移動コンポーネントの再開
        if (move != nullptr) move->Execute();
    }
}

void Component_PlayerBehavior::Dodge()
{
    holder_->SetShader(Direct3D::SHADER_TYPE::SHADER_UNLIT);
    UIPanel* panel_ = UIPanel::GetInstance();

    UIImage* focus = (UIImage*)panel_->FindObject("focus");
    // NOTE: 一度だけダッシュ処理を実行するためのフラグ
    static bool isDash = false;
    static float frameCount = 0;
    
    // プレイヤーのHPゲージコンポーネントを取得
    Component_HealthGauge* hg = (Component_HealthGauge*)(GetChildComponent("PlayerHealthGauge"));
    if(hg == nullptr)return;

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

        // 無敵へ変更
        frameCount = 0;
        hg->Lock();

        // ダッシュフラグを立てる
        isDash = true;


        focus->SetEnable(true);
    }
 
    // nフレーム経過語に、無敵状態を解除
    {
        frameCount++;
        
        if (frameCount >= InvincibilityFrame_) {
            hg->Unlock();
        }
    }

    // 突進処理が終了していたら...
    if (tackle->IsActived() == false) {

        holder_->SetShader(Direct3D::SHADER_TYPE::SHADER_3D);

        focus->SetEnable(false);

        // ダッシュフラグをリセット
		isDash = false;

        //移動を可能にする
        move->Execute();


        // 状態を遷移
        IsWASDKey() ? SetState(PLAYER_STATE_WALK) : SetState(PLAYER_STATE_IDLE);
    }
}

void Component_PlayerBehavior::Dead()
{
	// 移動コンポーネントの取得 & 有無の確認後、移動を不可能にする
	Component_WASDInputMove* move = (Component_WASDInputMove*)(GetChildComponent("InputMove"));
    if (move != nullptr)move->Stop();
}

bool Component_PlayerBehavior::IsDead()
{
    Component_PlayerMotion* motion = (Component_PlayerMotion*)(GetChildComponent("PlayerMotion"));

    if(motion!= nullptr) return motion->IsEnd() && nowState_ == PLAYER_STATE_DEAD;
    return false;
}

XMVECTOR Component_PlayerBehavior::CalcShootDirection()
{
    // FIX: 下記の処理が正常に動作しないため、カメラの視線ベクトルを返すように一時的に変更
    return Camera::GetSightLine();



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
        auto min_iter = std::min_element(hitRayCastDatalist.begin(), hitRayCastDatalist.end(), CompareDist());

        // イテレータが有効か確認して最小要素の dist を出力
        if (min_iter != hitRayCastDatalist.end()) {
            XMFLOAT3 holderPos = holder_->GetPosition();
            return XMVector3Normalize(XMLoadFloat3(&min_iter->pos) - XMLoadFloat3(&holderPos));
        }
    }

    // レイキャストデータリストが空だったら
    return Camera::GetSightLine();
}
