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

namespace
{
    const float SHOT_RATE = 0.2f;
    const float SHOT_ANGLE = 15;
    const int SHOT_TIME = 3;
    EFFEKSEERLIB::EFKTransform t;/*★★★*/
}

Component_BossBehavior::Component_BossBehavior(string _name, StageObject* _holder, Component* _parent)
    : Component(_holder, _name, BossBehavior, _parent), nowState_(WAIT), prevState_(WAIT), isActive_(false),
    shotrange_{}, tacklerange_{}, nextStateTime_{}, shotRate_(SHOT_RATE), rotateSpeed_(SHOT_ANGLE), target_(nullptr), angle_{}
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
    if (!FindChildComponent("CircleRangeDetector")) AddChildComponent(CreateComponent("CircleRangeDetector", CircleRangeDetector, holder_, this));
    if (!FindChildComponent("ShootAttack")) AddChildComponent(CreateComponent("ShootAttack", ShootAttack, holder_, this));
    if (!FindChildComponent("Timer")) AddChildComponent(CreateComponent("Timer", Timer, holder_, this));
    if (!FindChildComponent("TackleMove")) AddChildComponent(CreateComponent("TackleMove", TackleMove, holder_, this));
    if (!FindChildComponent("HealthGauge")) AddChildComponent(CreateComponent("HealthGauge", HealthGauge, holder_, this));


    // effekseer: :Effectの読み込み
    EFFEKSEERLIB::gEfk->AddEffect("sword", "Effects/Salamander12.efk");/*★★★*/

    // コライダーの追加
    // fix: コライダーのサイズを今後データから読み込むように変更
    holder_->AddCollider(new BoxCollider({}, {5.0f, 5.0f, 5.0f}));
}

void Component_BossBehavior::Update()
{
    if (target_ == nullptr) target_ = (StageObject*)holder_->GetParent()->FindObject(targetName_);

    static bool isGameStart = false;
    // ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
    // カウント制御されている場合の処理
    // ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
    CountDown* countDown = (CountDown*)(holder_->FindObject("CountDown"));
    if (countDown != nullptr && isGameStart == false) {

        // カウントダウンが終了した場合
        if (countDown->IsFinished()) {

            //移動を可能にする
            isActive_ = true;

            // ゲームスタートフラグを立てる
            isGameStart = true;
        }
        else {
            // 移動を不可能にする
			isActive_ = false;
        }
    }


    // hp表示
    Component_HealthGauge* hg = (Component_HealthGauge*)(GetChildComponent("HealthGauge"));
    ImGui::Begin("Cactann");
    ImGui::ProgressBar(static_cast<float>(hg->GetNow()) / hg->GetMax());
    ImGui::End();


    if (target_ == nullptr || !isActive_) return;

    switch (nowState_)
    {
    case WAIT:
        Wait();
        break;

    case SHOT:
        Shot();
        break;

    case TACKLE:
        Tackle();
        break;

    case SHOCK:
        Shock();
        break;
    }

    //prevState_ = nowState_;
}

void Component_BossBehavior::Release()
{
}

void Component_BossBehavior::OnCollision(GameObject* _target, Collider* _collider)
{
    Component_TackleMove* tackleMove = (Component_TackleMove*)(GetChildComponent("TackleMove"));
    if (tackleMove == nullptr) return;

    if (tackleMove->IsActived() == true && _target != nullptr) {
        for (auto hg : ((StageObject*)_target)->FindComponent(HealthGauge))((Component_HealthGauge*)hg)->TakeDamage(30);
    }
}

void Component_BossBehavior::Save(json& _saveObj)
{
    _saveObj["shootHeight_"] = shootHeight_;
    if (target_ != nullptr) _saveObj["target_"] = target_->GetObjectName();
    _saveObj["shotrange_"] = shotrange_;
    _saveObj["tacklerange_"] = tacklerange_;
    _saveObj["nextStateTime_"] = nextStateTime_;
    _saveObj["shotRate_"] = shotRate_;
    _saveObj["rotateSpeed_"] = rotateSpeed_;
}

void Component_BossBehavior::Load(json& _loadObj)
{
    if(_loadObj.contains("shootHeight_")) shootHeight_ = _loadObj["shootHeight_"];
    if (_loadObj.contains("target_")) targetName_ = _loadObj["target_"];
    if (_loadObj.contains("shotrange_")) shotrange_ = _loadObj["shotrange_"];
    if (_loadObj.contains("tacklerange_")) tacklerange_ = _loadObj["tacklerange_"];
    if (_loadObj.contains("nextStateTime_")) nextStateTime_ = _loadObj["nextStateTime_"];
    if (_loadObj.contains("shotRate_")) shotRate_ = _loadObj["shotRate_"];
    if (_loadObj.contains("rotateSpeed_")) rotateSpeed_ = _loadObj["rotateSpeed_"];
}

void Component_BossBehavior::DrawData()
{

    ImGui::DragFloat("shootHeight_", &shootHeight_);
    ImGui::DragFloat("shotrange_", &shotrange_);
    ImGui::DragFloat("tacklerange_", &tacklerange_);
    ImGui::DragFloat("nextStateTime_", &nextStateTime_);
    ImGui::DragFloat("shotRate_", &shotRate_);
    ImGui::DragFloat("rotateSpeed_", &rotateSpeed_);
#ifdef _DEBUG
    auto timer = dynamic_cast<Component_Timer*>(GetChildComponent("Timer"));
    if (timer == nullptr) return;

    ImGui::Text("%f", holder_->GetRotate().y);
    ImGui::Text("%f", timer->GetNowTime());

    if (ImGui::Checkbox("Activate", &isActive_));
        

    // 対象の選択
    vector<string> objNames;
    objNames.push_back("null");

    for (auto obj : ((Stage*)holder_->GetParent())->GetStageObjects()) objNames.push_back(obj->GetObjectName());

    static int select = 0;
    if (ImGui::BeginCombo("target_", objNames[select].c_str())) {
        for (int i = 0; i < objNames.size(); i++) {
            bool is_selected = (select == i);
            if (ImGui::Selectable(objNames[i].c_str(), is_selected)) select = i;
            if (is_selected) ImGui::SetItemDefaultFocus();
        }
        ImGui::EndCombo();
    }

    if (select == 0) target_ = nullptr;
    else {
        target_ = (StageObject*)holder_->FindObject(objNames[select]);

        auto detector = dynamic_cast<Component_CircleRangeDetector*>(GetChildComponent("CircleRangeDetector"));
        detector->SetTarget(target_);
    }
#endif // _DEBUG
}

void Component_BossBehavior::Shot()
{
    auto shoot = dynamic_cast<Component_ShootAttack*>(GetChildComponent("ShootAttack"));
    if (shoot == nullptr) return;
    auto timer = dynamic_cast<Component_Timer*>(GetChildComponent("Timer"));
    if (timer == nullptr) return;
    timer->SetTime(SHOT_TIME);
    timer->Start();


    angle_ += rotateSpeed_;
    holder_->SetRotateY(angle_);

    if (timer->IsIntervalTime(shotRate_)) {
        // 撃ち放つ方向を設定
        XMFLOAT3 holderRotate = holder_->GetRotate();

        XMVECTOR myDirection = { 0,0,1,0 };

        myDirection = XMVector3TransformCoord(myDirection, XMMatrixRotationY(XMConvertToRadians(holderRotate.y)));

        shoot->SetShootingDirection(myDirection);

        // 撃ち放つ位置を設定
        XMFLOAT3 shootPosition = holder_->GetPosition();
        shootPosition.y += shootHeight_;
        shoot->SetShootingPosition(shootPosition);

        // 撃つ
        shoot->Execute();
    }

    if (timer->GetIsEnd()) {
        // 状態をWAITに変更し、タイマーを開始
        nowState_ = WAIT;
        timer->Reset();
        angle_ = 0;
    }
}

void Component_BossBehavior::Tackle()
{
    auto tackleMove = dynamic_cast<Component_TackleMove*>(GetChildComponent("TackleMove"));
    if (tackleMove == nullptr) return;

    /*auto tackleDetector = dynamic_cast<Component_CircleRangeDetector*>(GetChildComponent("CircleRangeDetector"));
    if (tackleDetector == nullptr || !tackleDetector->IsContains()) {
        nowState_ = WAIT;
        return;
    }*/

    XMFLOAT3 holderPosition = holder_->GetPosition();
    XMFLOAT3 targetPos = target_->GetPosition();

    // 方向ベクトルの計算
    XMVECTOR direction = XMVector3Normalize(XMLoadFloat3(&targetPos) - XMLoadFloat3(&holderPosition));
    direction = XMVectorSetY(direction, 0);

    // 距離の計算
    float distance = XMVectorGetX(XMVector3Length(XMLoadFloat3(&targetPos) - XMLoadFloat3(&holderPosition)));

    // TackleMove コンポーネントに方向と距離を設定
    tackleMove->SetDirection(direction);
    tackleMove->SetDistance(distance);

    // 突進を実行
    tackleMove->Execute();

    // 状態をWAITに変更し、タイマーを開始
    nowState_ = WAIT;
}

void Component_BossBehavior::Shock()
{
    // ショック状態の処理を実装
    // ...

    // 状態をWAITに変更し、タイマーを開始
    nowState_ = WAIT;
}

void Component_BossBehavior::Wait()
{
    auto timer = dynamic_cast<Component_Timer*>(GetChildComponent("Timer"));
    if (timer == nullptr) return;
    timer->SetTime(nextStateTime_);
    timer->Start();
    if (timer->GetIsEnd()) {
        RandomTransition();
        timer->Reset();
    }
}

void Component_BossBehavior::RandomTransition()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, 1); // 0から2の範囲で乱数を生成

    int nextState = dist(gen);

    switch (nextState)
    {
    case 0:
        nowState_ = SHOT;
        break;
    case 1:
        nowState_ = TACKLE;

        // effekseer: :Effectの再生情報の設定

        DirectX::XMStoreFloat4x4(&(t.matrix), holder_->GetWorldMatrix());/*★★★*/
        t.isLoop = false;/*★★★*/
        t.maxFrame = 60;/*★★★*/
        t.speed = 1.0f;/*★★★*/


        // effekseer: :Effectの再生
        mt = EFFEKSEERLIB::gEfk->Play("sword", t);/*★★★*/

        break;
    case 2:
        nowState_ = SHOCK;
        break;
    }
}