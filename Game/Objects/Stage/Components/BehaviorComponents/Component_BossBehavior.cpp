#include "Component_BossBehavior.h"

// �C���N���[�h
#include "../../StageObject.h"
#include "../TimerComponent/Component_Timer.h"
#include "../AttackComponents/Component_ShootAttack.h"
#include "../DetectorComponents/Component_CircleRangeDetector.h"
#include "../MoveComponents/Component_TackleMove.h"
#include "../../../../../Engine/ImGui/imgui.h"
#include "../../Stage.h"
#include "../../../../../Engine/Global.h"
#include <random>

namespace
{
    const float SHOT_RATE = 0.2f;
    const float SHOT_ANGLE = 25;
    const int SHOT_TIME = 3;
}

Component_BossBehavior::Component_BossBehavior(string _name, StageObject* _holder, Component* _parent)
    : Component(_holder, _name, BossBehavior, _parent), nowState_(WAIT), prevState_(WAIT), isActive_(false),
    target_(nullptr), shotrange_{}, tacklerange_{}, nextStateTime_{}
{
}

void Component_BossBehavior::Initialize()
{
    // �K�v�ȃR���|�[�l���g��ǉ�
    if (!FindChildComponent("CircleRangeDetector")) AddChildComponent(CreateComponent("CircleRangeDetector", CircleRangeDetector, holder_, this));
    if (!FindChildComponent("ShootAttack")) AddChildComponent(CreateComponent("ShootAttack", ShootAttack, holder_, this));
    if (!FindChildComponent("Timer")) AddChildComponent(CreateComponent("Timer", Timer, holder_, this));
    if (!FindChildComponent("TackleMove")) AddChildComponent(CreateComponent("TackleMove", TackleMove, holder_, this));
}

void Component_BossBehavior::Update()
{
    if (target_ == nullptr) target_ = (StageObject*)holder_->FindObject(targetName_);
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

void Component_BossBehavior::OnCollision(GameObject* _target)
{
}

void Component_BossBehavior::Save(json& _saveObj)
{
    if (target_ != nullptr) _saveObj["target_"] = target_->GetObjectName();
    _saveObj["shotrange_"] = shotrange_;
    _saveObj["tacklerange_"] = tacklerange_;
    _saveObj["nextStateTime_"] = nextStateTime_;
}

void Component_BossBehavior::Load(json& _loadObj)
{
    if (_loadObj.contains("target_")) targetName_ = _loadObj["target_"];
    if (_loadObj.contains("shotrange_")) shotrange_ = _loadObj["shotrange_"];
    if (_loadObj.contains("tacklerange_")) tacklerange_ = _loadObj["tacklerange_"];
    if (_loadObj.contains("nextStateTime_")) nextStateTime_ = _loadObj["nextStateTime_"];
}

void Component_BossBehavior::DrawData()
{
    ImGui::DragFloat("shotrange_", &shotrange_);
    ImGui::DragFloat("tacklerange_", &tacklerange_);
    ImGui::DragFloat("nextStateTime_", &nextStateTime_);
#ifdef _DEBUG
    auto timer = dynamic_cast<Component_Timer*>(GetChildComponent("Timer"));
    if (timer == nullptr) return;

    ImGui::Text("%f", holder_->GetRotate().y);
    ImGui::Text("%f", timer->GetNowTime());

    if (ImGui::Button("Activate"))
        isActive_ = true;

    // �Ώۂ̑I��
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

    static float angle = 0;
    angle += SHOT_ANGLE;
    holder_->SetRotateY(angle);

    if (timer->IsIntervalTime(SHOT_RATE)) {
        // ������������ݒ�
        XMFLOAT3 holderRotate = holder_->GetRotate();

        XMVECTOR myDirection = { 0,0,1,0 };

        myDirection = XMVector3TransformCoord(myDirection, XMMatrixRotationY(XMConvertToRadians(holderRotate.y)));

        shoot->SetShootingDirection(myDirection);
        // ����
        shoot->Execute();
    }

    if (timer->GetIsEnd()) {
        // ��Ԃ�WAIT�ɕύX���A�^�C�}�[���J�n
        nowState_ = WAIT;
        timer->Reset();
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

    // �����x�N�g���̌v�Z
    XMVECTOR direction = XMVector3Normalize(XMLoadFloat3(&targetPos) - XMLoadFloat3(&holderPosition));

    // �����̌v�Z
    float distance = XMVectorGetX(XMVector3Length(XMLoadFloat3(&targetPos) - XMLoadFloat3(&holderPosition)));

    // TackleMove �R���|�[�l���g�ɕ����Ƌ�����ݒ�
    tackleMove->SetDirection(direction);
    tackleMove->SetDistance(distance);

    // �ːi�����s
    tackleMove->Execute();

    // ��Ԃ�WAIT�ɕύX���A�^�C�}�[���J�n
    nowState_ = WAIT;
}

void Component_BossBehavior::Shock()
{
    // �V���b�N��Ԃ̏���������
    // ...

    // ��Ԃ�WAIT�ɕύX���A�^�C�}�[���J�n
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
    std::uniform_int_distribution<> dist(0, 2); // 0����2�͈̔͂ŗ����𐶐�

    int nextState = dist(gen);

    switch (nextState)
    {
    case 0:
        nowState_ = SHOT;
        break;
    case 1:
        nowState_ = TACKLE;
        break;
    case 2:
        nowState_ = SHOCK;
        break;
    }
}