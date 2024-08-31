#include "Component_CactanBehavior.h"

#include "../../../../../Engine/Global.h"
#include "../../../../../Engine/ImGui/imgui.h"
#include "../../Stage.h"
#include "../../StageObject.h" 
#include "../AttackComponents/Component_ShootAttack.h"
#include "../DetectorComponents/Component_CircleRangeDetector.h"
#include "../GaugeComponents/Component_HealthGauge.h"

#include "../TimerComponent/Component_Timer.h"
#include"../../../../Engine/ResourceManager/Model.h"
Component_CactanBehavior::Component_CactanBehavior(string _name, StageObject* _holder, Component* _parent)
	:Component(_holder, _name, CactanBehavior, _parent), cactanBulletModelHandle_(-1)
{
}

void Component_CactanBehavior::Initialize()
{
	holder_->SetAttribute(ENEMY);
	holder_->AddCollider(new BoxCollider(XMFLOAT3(0, 0, 0), XMFLOAT3(1, 1, 1)));

	// �K�v�ȃR���|�[�l���g��ǉ�
	if (FindChildComponent("CircleRangeDetector") == false)AddChildComponent(CreateComponent("CircleRangeDetector", CircleRangeDetector, holder_, this));
	if (FindChildComponent("ShootAttack") == false)AddChildComponent(CreateComponent("ShootAttack", ShootAttack, holder_, this));
	if (FindChildComponent("Timer") == false)AddChildComponent(CreateComponent("Timer", Timer, holder_, this));
	if (FindChildComponent("HealthGauge") == false)AddChildComponent(CreateComponent("HealthGauge", HealthGauge, holder_, this));

	cactanBulletModelHandle_ = Model::Load("Models/DebugCollision/SphereCollider.fbx");
	assert(cactanBulletModelHandle_ >= 0);

}

void Component_CactanBehavior::Update()
{
	if (target_ == nullptr)target_ = (StageObject*)holder_->FindObject(targetName_);
	if (target_ == nullptr)return;

	auto detector = dynamic_cast<Component_CircleRangeDetector*>(GetChildComponent("CircleRangeDetector"));
	if (detector == nullptr)return;

	// �͈͓��Ƀv���C���[������ꍇ
	if (detector->IsContains()) {

		// �^�C�}�[���J�n
		auto timer = dynamic_cast<Component_Timer*>(GetChildComponent("Timer"));
		if (timer == nullptr)return;
		timer->Start();

		// 3�b���ƂɃV���[�g�A�^�b�N�����s
		if (timer->IsIntervalTime(3.f)) {

			auto shoot = dynamic_cast<Component_ShootAttack*>(GetChildComponent("ShootAttack"));
			if (shoot == nullptr)return;
			shoot->SetBulletModelHandle(cactanBulletModelHandle_);
			// ������������ݒ�
			XMFLOAT3 holderPos = holder_->GetPosition();
			XMFLOAT3 targetPos = target_->GetPosition();
			shoot->SetShootingDirection(XMVector3Normalize(XMLoadFloat3(&targetPos) - XMLoadFloat3(&holderPos)));

			// ����
			shoot->Execute();
		}
	}
	else {


		// �^�C�}�[���~
		auto timer = dynamic_cast<Component_Timer*>(GetChildComponent("Timer"));
		if (timer == nullptr)return;
		timer->Stop();
	}

}

void Component_CactanBehavior::Release()
{
}

void Component_CactanBehavior::Save(json& _saveObj)
{
	if (target_ != nullptr)_saveObj["target_"] = target_->GetObjectName();
}

void Component_CactanBehavior::Load(json& _loadObj)
{
	if (_loadObj.contains("target_"))targetName_ = _loadObj["target_"];
}

void Component_CactanBehavior::DrawData()
{
#ifdef _DEBUG

	//�Ώۂ̑I��
	vector<string> objNames;
	objNames.push_back("null");

	for (auto obj : ((Stage*)holder_->GetParent())->GetStageObjects())objNames.push_back(obj->GetObjectName());

	static int select = 0;
	if (ImGui::BeginCombo("target_", objNames[select].c_str())) {
		for (int i = 0; i < objNames.size(); i++) {
			bool is_selected = (select == i);
			if (ImGui::Selectable(objNames[i].c_str(), is_selected))select = i;
			if (is_selected)ImGui::SetItemDefaultFocus();
		}
		ImGui::EndCombo();
	}

	if (select == 0)target_ = nullptr;
	else {
		target_ = (StageObject*)holder_->FindObject(objNames[select]);

		auto detector = dynamic_cast<Component_CircleRangeDetector*>(GetChildComponent("CircleRangeDetector"));
		detector->SetTarget(target_);
	}
#endif // _DEBUG

}
