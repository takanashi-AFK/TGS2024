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
	if (FindChildComponent("CircleRangeDetector") == false)AddChildComponent(CreateComponent("CircleRangeDector", CircleRangeDetector, holder_, this));
	if (FindChildComponent("ShootAttack") == false)AddChildComponent(CreateComponent("ShootAttack", ShootAttack, holder_, this));
	if (FindChildComponent("HealthGauge") == false)AddChildComponent(CreateComponent("HealthGauge", HealthGauge, holder_, this));
	if (FindChildComponent("Timer") == false)AddChildComponent(CreateComponent("Timer", Timer, holder_, this));
}

void Component_KingCactanBehavior::Update()
{
	if (target_ == nullptr)target_ = (StageObject*)holder_->FindObject(targetName_);
	if (target_ == nullptr)return;

	Component* comp = GetChildComponent("CircleRangeDetector");
	Component_CircleRangeDetector* detector = dynamic_cast<Component_CircleRangeDetector*>(comp);
	if (detector == nullptr)return;

	//ƒ^[ƒQƒbƒg‚ª”ÍˆÍ“à‚É‚¢‚éê‡
	if (detector->IsContains()) {

		Component* timerComp = GetChildComponent("Timer");
		Component_Timer* timer = dynamic_cast<Component_Timer*>(timerComp);
		if (timer == nullptr)return;
		timer->Start();

		Component* chaseComp = GetChildComponent("Chase");
		Component_Chase* chase = dynamic_cast<Component_Chase*>(chaseComp);
		if (chase == nullptr)return;

		//n•b‚²‚Æ‚Éƒ`ƒFƒCƒX‚ðŽÀs
		if (timer->SetTime()) {

			chase->SetTarget(target_);
			chase->Start();

		}
		else {

			chase->Stop();
			timer->Stop();


			Component* shootcomp = GetChildComponent("ShootAttack");
			Component_ShootAttack* shoot = dynamic_cast<Component_ShootAttack*>(shootcomp);
			if (shoot == nullptr) return;
			XMFLOAT3 holderPos = holder_->GetPosition();
			XMFLOAT3 targetPos = target_->GetPosition();
			shoot->SetShootingDirection(XMVector3Normalize(XMLoadFloat3(&targetPos) - XMLoadFloat3(&holderPos)));
			shoot->Execute();

		}
	}
	else {

		Component* timecomp = GetChildComponent("Timer");
		Component_Timer* time = dynamic_cast<Component_Timer*>(timecomp);
		if (time == nullptr)return;
		time->Stop();

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