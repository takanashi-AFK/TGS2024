#include "Component_BossBehavior.h"

// インクルード
#include "../../StageObject.h"
#include "../TimerComponent/Component_Timer.h"
#include "../AttackComponents/Component_ShootAttack.h"
#include "../DetectorComponents/Component_CircleRangeDetector.h"
#include "../MoveComponents/Component_TackleMove.h"
#include "../../../../../Engine/ImGui/imgui.h"
#include "../../Stage.h"
#include "../../../../../Engine/Global.h"
#include <random>
#include "../../../UI/CountDown.h"
#include "../GaugeComponents/Component_HealthGauge.h"
#include "../../../UI/UIPanel.h"
#include "../../../UI/UIProgressBar.h"
#include "../../../../Constants.h"

using namespace Constants;

namespace
{
    const float SHOT_RATE = 0.2f;
    const float SHOT_ANGLE = 15;
    const int SHOT_TIME = 5;
	const float SMALL_VEROSITY = 0.02f;
    EFFEKSEERLIB::EFKTransform t;/*★★★*/
}

Component_BossBehavior::Component_BossBehavior(string _name, StageObject* _holder, Component* _parent)
    : Component(_holder, _name, BossBehavior, _parent)
{
#ifdef _DEBUG
    isActive_ = false;
#else
    isActive_ = true;
#endif // DEBUG

}

void Component_BossBehavior::Initialize()
{
    // 必要なコンポーネントを追加
    if (!FindChildComponent("ShootAttack")) AddChildComponent(CreateComponent("ShootAttack", ShootAttack, holder_, this));
    if (!FindChildComponent("Timer")) AddChildComponent(CreateComponent("Timer", Timer, holder_, this));
    if (!FindChildComponent("TackleMove")) AddChildComponent(CreateComponent("TackleMove", TackleMove, holder_, this));
    if (!FindChildComponent("HealthGauge")) AddChildComponent(CreateComponent("HealthGauge", HealthGauge, holder_, this));

    // effekseer: :Effectの読み込み
    EFFEKSEERLIB::gEfk->AddEffect("sword", "Effects/Salamander12.efk");/*★★★*/
	EFFEKSEERLIB::gEfk->AddEffect("fire", "Effects/Fire3.efk");/*★★★*/

    // コライダーの追加
    // fix: コライダーのサイズを今後データから読み込むように変更
    holder_->AddCollider(new BoxCollider({}, { 5.0f, 5.0f, 5.0f }));
}

void Component_BossBehavior::Update()
{
    // ターゲットの取得
    if (target_ == nullptr) target_ = (StageObject*)holder_->FindObject(targetName_);

    // カウント制御されている場合の処理
    CountDown* countDown = (CountDown*)(holder_->FindObject("CountDown"));
    if (countDown != nullptr && isGameStart_ == false) {

        // カウントダウンが終了した場合
        if (countDown->IsFinished()) {

            //移動を可能にする
            isActive_ = true;

            // ゲームスタートフラグを立てる
            isGameStart_ = true;
        }
        else {
            // 移動を不可能にする
            isActive_ = false;
            return;
        }
    }

    // 対象が存在しない または アクティブでない場合は処理を行わない
    if (target_ == nullptr || !isActive_) return;


    // HP関連処理
    {
        // ボスのHPゲージコンポーネントを取得
        Component_HealthGauge* hg = (Component_HealthGauge*)(GetChildComponent("HealthGauge"));

        // UIProgressBarを取得
        UIProgressBar* hpBar = (UIProgressBar*)UIPanel::GetInstance()->FindObject(PLAY_SCENE_BOSS_HP_GAUGE_NAME);

        // HPバーの値を設定
        if (hpBar != nullptr && hg != nullptr)hpBar->SetProgress(&hg->now_, &hg->max_);

        // HPが0以下になったら... DEAD状態に遷移
        if (hg != nullptr)if (hg->IsDead() == true)SetState(BOSS_STATE_DEAD);
    }

    // 状態によって処理を分岐
    switch (nowState_)
    {
    case BOSS_STATE_IDLE:Idle(); break;
    case BOSS_STATE_SHOT:Shot(); break;
    case BOSS_STATE_TACKLE:Tackle(); break;
    case BOSS_STATE_DEAD:Dead(); break;
    }

}

void Component_BossBehavior::Release()
{
}

void Component_BossBehavior::OnCollision(GameObject* _target, Collider* _collider)
{
    // 突進攻撃によるダメージ処理
    {
        for (auto tackleMove : GetChildComponent(ComponentType::TackleMove)){

            // 突進攻撃がアクティブでない または 対象が存在しない場合は処理を行わない
            if (!((Component_TackleMove*)tackleMove)->IsActived() || _target == nullptr) continue;

            // 対象のHPを減少
            for (auto hg : ((StageObject*)_target)->FindComponent(HealthGauge))((Component_HealthGauge*)hg)->TakeDamage(30);
        }
    }
}

void Component_BossBehavior::Save(json& _saveObj)
{
    // 対象の名前を保存
    if (target_ != nullptr) _saveObj["target_"] = target_->GetObjectName();
    
    // 発射間枠を保存
    _saveObj["shotInterval_"] = shotInterval_;
    
    // 射撃の高さを保存
    _saveObj["shootHeight_"] = shootHeight_;
    
    // 状態変更遅延を保存
    _saveObj["stateChangeDelay_"] = stateChangeDelay_;
}

void Component_BossBehavior::Load(json& _loadObj)
{
    // 対象の名前を読み込み
    if (_loadObj.contains("target_")) targetName_ = _loadObj["target_"];
    
    // 発射間隔を読み込み
    if (_loadObj.contains("shotInterval_")) shotInterval_ = _loadObj["shotInterval_"];

    // 射撃の高さを読み込み
    if(_loadObj.contains("shootHeight_")) shootHeight_ = _loadObj["shootHeight_"];
    
    // 状態変更遅延を読み込み
    if (_loadObj.contains("stateChangeDelay_")) stateChangeDelay_ = _loadObj["stateChangeDelay_"];
}

void Component_BossBehavior::DrawData()
{
    // アクティブフラグを表示
    ImGui::Checkbox("isActive_", &isActive_);
    // 対象を設定
    {
        // ステージ上に存在するオブジェクトの名前を全て取得
        vector<string> nameList{};nameList.push_back("None");
        for (auto obj : ((Stage*)holder_->FindObject("Stage"))->GetStageObjects()) nameList.push_back(obj->GetObjectName());

        // コンボボックスで選択
        static int select = 0;
        if (ImGui::BeginCombo("target_", nameList[select].c_str())) {
            for (int i = 0; i < nameList.size(); i++) {
                bool is_selected = (select == i);
                if (ImGui::Selectable(nameList[i].c_str(), is_selected)) select = i;
                if (is_selected) ImGui::SetItemDefaultFocus();
            }
            ImGui::EndCombo();
        }

        // 選択された名前から対象を設定
        if (select != 0) target_ = (StageObject*)holder_->FindObject(nameList[select]);
    }

    // 発射間隔を表示
    ImGui::DragFloat("shotInterval_", &shotInterval_);
    
    // 射撃の高さを表示
    ImGui::DragFloat("shootHeight_", &shootHeight_);
    
    // 状態変更遅延を表示
    ImGui::DragFloat("stateChangeDelay_", &stateChangeDelay_);
}

bool Component_BossBehavior::IsDead()
{
    // ボスの状態がDEADであり、大きさが0以下の場合
    return (nowState_ == BOSS_STATE_DEAD && holder_->GetScale().x <= 0);
}

BossState Component_BossBehavior::RandomStatePick()
{
    // 抽選結果を格納する変数を用意
    BossState res = BOSS_STATE_MAX;

    // 状態を抽選　ただし、IDLEとDEADは除外
    do res = (BossState)(rand() % BOSS_STATE_MAX);
    while (res == BOSS_STATE_IDLE || res == BOSS_STATE_DEAD);

    // 抽選結果を返す
    return res;
}

void Component_BossBehavior::Shot()
{
    // 射撃攻撃コンポーネントの取得 & nullチェック
    Component_ShootAttack* shoot = (Component_ShootAttack*)GetChildComponent("ShootAttack");

    // タイマーの取得 & nullチェック
    Component_Timer* timer = (Component_Timer*)GetChildComponent("Timer");
    if (timer == nullptr || shoot == nullptr) return;

    // タイマーの設定 & 開始
    timer->SetTime(SHOT_TIME);
    timer->Start();

    // 角度を格納する変数を用意
    static float angle = 0;
    static float rotateSpeed = 1.f + (rand() % 15);

    // 所有者の角度を更新
    angle += rotateSpeed;
    holder_->SetRotateY(angle);

    // タイマーが一定時間経過した場合
    if (timer->IsIntervalTime(shotInterval_)) {

        // 発射方向を設定
        XMVECTOR dir = { 0,0,1,0 };
        shoot->SetShootingDirection(XMVector3TransformCoord(dir, XMMatrixRotationY(XMConvertToRadians(holder_->GetRotate().y))));

        // 発射位置を設定
        XMFLOAT3 shootPosition = holder_->GetPosition();
        shootPosition.y += shootHeight_;
        shoot->SetShootingPosition(shootPosition);

        // 発射
        shoot->Execute();
    }

    // タイマーが終了した場合
    if (timer->GetIsEnd()) {
        
        // 待機状態に遷移
        SetState(BOSS_STATE_IDLE);

        // タイマーをリセット
        timer->Reset();

        // 角度をリセット
        angle = 0;

        // 回転速度を 1.fから15.fの範囲でランダムに設定
        rotateSpeed = 1.f + (rand() % 15);
    }
}

void Component_BossBehavior::Tackle()
{
    // 初回フラグを用意
    static bool isFirst = true;

    // 突進行動コンポーネントの取得 & nullチェック
    Component_TackleMove* tackleMove = (Component_TackleMove*)GetChildComponent("TackleMove");
    if (tackleMove == nullptr) return;

    // 初回のみ処理を行う
    if (isFirst) {
		// 突進攻撃の初回フラグをfalseに設定
		isFirst = false;

        // プレイヤーの方向を向く
		{
			// 所有者の位置を取得
            XMFLOAT3 holderPos = holder_->GetPosition();

			// 対象の位置を取得
			XMFLOAT3 targetPos = target_->GetPosition();

			// 所有者の位置を対象の位置に向ける
			holder_->SetRotateY(atan2f(targetPos.z - holderPos.z, targetPos.x - holderPos.x) * 180 / XM_PI);
		}
        
        // 突進攻撃を実行
        {
			// 情報の取得
			// 所有者の位置を取得
			XMFLOAT3 holderPos = holder_->GetPosition();

			// 対象の位置を取得
			XMFLOAT3 targetPos = target_->GetPosition();

			// 突進方向を設定 
			tackleMove->SetDirection(XMVectorSetY(XMVector3Normalize(XMLoadFloat3(&targetPos) - XMLoadFloat3(&holderPos)), 0));

			// 距離を設定
			tackleMove->SetDistance(XMVectorGetX(XMVector3Length(XMLoadFloat3(&targetPos) - XMLoadFloat3(&holderPos))));

			// 突進を実行
			tackleMove->Execute();
        }

        // エフェクトを再生
        {
            // 情報の設定
            DirectX::XMStoreFloat4x4(&(t.matrix), holder_->GetWorldMatrix());
            t.isLoop = false;
            t.maxFrame = 60;
            t.speed = 1.0f;

            // 再生
            mt = EFFEKSEERLIB::gEfk->Play("sword", t);
        }
	}

    // 突進攻撃が終了した場合
    if (tackleMove->IsActived() == false) { SetState(BOSS_STATE_IDLE); isFirst = true; }
}

void Component_BossBehavior::Idle()
{
    // タイマーの取得 & nullチェック
    Component_Timer* timer = (Component_Timer*)GetChildComponent("Timer");
    if (timer == nullptr) return;

    // タイマーの設定
    {
        // 状態を遷移するまでの時間を設定
        timer->SetTime(stateChangeDelay_);

        // タイマーを開始
        timer->Start();
    }

    // タイマーが終了した場合
    if (timer->GetIsEnd()) {

        // ランダムに状態を遷移
        SetState(RandomStatePick());

        // タイマーをリセット
        timer->Reset();
    }
}

void Component_BossBehavior::Dead()
{

    Transform effectTransform;
	effectTransform.position_ = holder_->GetPosition();

    // 大きさが０でない場合
    if (holder_->GetScale().x >= 0) {
    // キャラクターの大きさを徐々に小さくする
    holder_->SetScale(holder_->GetScale().x - SMALL_VEROSITY);
    }
    else {
        // 情報の設定
        DirectX::XMStoreFloat4x4(&(t.matrix), effectTransform.GetWorldMatrix());
        t.isLoop = false;
        t.maxFrame = 60;
        t.speed = 1.0f;

        // 再生
        mt = EFFEKSEERLIB::gEfk->Play("fire", t);
    }
}