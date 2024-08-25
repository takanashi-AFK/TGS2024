#include "Component_KingCactanBehavior.h"

#include"../../../../Engine/ImGui/imgui.h"
#include"../../../../Engine/Global.h"
#include "../../Stage.h"
#include "../../StageObject.h" 
#include"../MoveComponents/Component_Chase.h"
#include"../DetectorComponents/Component_CircleRangeDetector.h"
#include"../AttackComponents/Component_ShootAttack.h"
#include"../GaugeComponents/Component_HealthGauge.h"
#include"../TimerComponent/Component_Timer.h"

Component_KingCactanBehavior::Component_KingCactanBehavior(string _name, StageObject* _holder, Component* _parent)
	:Component(_holder, _name, KingCactanBehavior, _parent)
{
}

void Component_KingCactanBehavior::Initialize()
{
	holder_->AddCollider(new BoxCollider(XMFLOAT3(0, 0, 0), XMFLOAT3(5, 5, 5)));

	if (FindChildComponent("Chase") == false)AddChildComponent(CreateComponent("Chase", Chase, holder_, this));
	if (FindChildComponent("CircleRangewDetector") == false)AddChildComponent(CreateComponent("CircleRangeDector", CircleRangeDetector, holder_, this));
	if (FindChildComponent("ShootAttack") == false)AddChildComponent(CreateComponent("ShootAttack", ShootAttack, holder_, this));
	if (FindChildComponent("HealthGauge") == false)AddChildComponent(CreateComponent("HealthGauge", HealthGauge, holder_, this));
	if (FindChildComponent("Timer") == false)AddChildComponent(CreateComponent("Timer", Timer, holder_, this));
}

void Component_KingCactanBehavior::Update()
{
	if (target_ == nullptr)target_ = (StageObject*)holder_->FindObject(targetName_);
	if (target_ == nullptr)return;

	Component_CircleRangeDetector* detector = dynamic_cast<Component_CircleRangeDetector*>(GetChildComponent("CircleRangeDector"));
	if (detector == nullptr)return;

	//ƒvƒŒƒCƒ„[‚ª”ÍˆÍ“à‚É‚¢‚éê‡
	if (detector->IsContains()) {

		Component_Timer* timer = dynamic_cast<Component_Timer*>(GetChildComponent("Timer"));
		if (timer == nullptr)return;
		timer->Start();

		//5•b‚²‚Æ‚Éƒ`ƒFƒCƒX‚ðŽÀs
		if (timer->IsIntervalTime(5.f)) {

			Component_Chase* chase = dynamic_cast<Component_Chase*>(GetChildComponent("Chase"));
			if (chase == nullptr)return;
			chase->SetTarget(target_);
			chase->Start();

		}
		else {

			Component_Chase* chase = dynamic_cast<Component_Chase*>(GetChildComponent("Chase"));
			if (chase == nullptr)return;
			chase->Stop();
			timer->Stop();

			Component_ShootAttack* shoot = dynamic_cast<Component_ShootAttack*>(GetChildComponent("ShootAttack"));
			if (shoot == nullptr) return;
			XMFLOAT3 holderPos = holder_->GetPosition();
			XMFLOAT3 targetPos = target_->GetPosition();
			shoot->SetShootingDirection(XMVector3Normalize(XMLoadFloat3(&targetPos) - XMLoadFloat3(&holderPos)));
			shoot->Execute();

		}
	}
	else {

		Component_Timer* timer = dynamic_cast<Component_Timer*>(GetChildComponent("Timer"));
		if (timer == nullptr)return;
		timer->Stop();

	}
}

void Component_KingCactanBehavior::Release()
{
}

void Component_KingCactanBehavior::Save(json& _saveObj)
{
	if (target_ != nullptr)_saveObj["target_"] = target_->GetObjectName();
}

void Component_KingCactanBehavior::Load(json& _loadObj)
{
	if (_loadObj.contains("target_"))targetName_ = _loadObj["target_"];
}

void Component_KingCactanBehavior::DrawData()
{
#ifdef _DEBUG

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

	/*if (select == 0)target_ = nullptr;
	else {
		target_ = (StageObject*)holder_->FindObject(objNames[select]);

		auto detector = dynamic_cast<Component_CircleRangeDetector*>(GetChildComponent("CircleRangeDetector"));
		detector->SetTarget(target_);
	}*/

#endif // _DEBUG
}

//5•b’Ç]->Ž~‚Ü‚é->Œ‚‚Â->‚Ü‚½“®‚­‚ÌŒJ‚è•Ô‚µ