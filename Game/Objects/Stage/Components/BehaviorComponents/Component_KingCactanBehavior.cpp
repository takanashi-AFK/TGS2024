#include "Component_KingCactanBehavior.h"

#include"../../../../../Engine/ImGui/imgui.h"
#include"../../../../../Engine/Global.h"
#include "../../Stage.h"
#include "../../StageObject.h" 
#include"../MoveComponents/Component_Chase.h"
#include"../DetectorComponents/Component_CircleRangeDetector.h"
#include"../AttackComponents/Component_ShootAttack.h"
#include"../GaugeComponents/Component_HealthGauge.h"
#include"../TimerComponent/Component_Timer.h"
#include"../../Bullet.h"
Component_KingCactanBehavior::Component_KingCactanBehavior(string _name, StageObject* _holder, Component* _parent)
	:Component(_holder, _name, KingCactanBehavior, _parent)
{
}

void Component_KingCactanBehavior::Initialize()
{
	holder_->AddCollider(new BoxCollider(XMFLOAT3(0, 0, 0), XMFLOAT3(5, 5, 5)));

	if (FindChildComponent("ChaseComponent") == false)AddChildComponent(CreateComponent("ChaseComponent", Chase, holder_, this));
	if (FindChildComponent("CircleRangeDetectorComponent") == false)AddChildComponent(CreateComponent("CircleRangeDetectorComponent", CircleRangeDetector, holder_, this));
	if (FindChildComponent("ShootAttackComponent") == false)AddChildComponent(CreateComponent("ShootAttackComponent", ShootAttack, holder_, this));
	if (FindChildComponent("HealthGaugeComponent") == false)AddChildComponent(CreateComponent("HealthGaugeComponent", HealthGauge, holder_, this));
	if (FindChildComponent("TimerComponent") == false)AddChildComponent(CreateComponent("TimerComponent", Timer, holder_, this));


}

void Component_KingCactanBehavior::Update()
{
	//ターゲットがいるかどうか
	if (target_ == nullptr)target_ = (StageObject*)holder_->FindObject(targetName_);
	if (target_ == nullptr)return;

	Component* comp = GetChildComponent("CircleRangeDetectorComponent");
	Component_CircleRangeDetector* detector = dynamic_cast<Component_CircleRangeDetector*>(comp);
	if (detector == nullptr)return;

	//ターゲットが範囲内にいる場合
	if (detector->IsContains()) {

		Component* timerComp = GetChildComponent("TimerComponent");
		Component_Timer* timer = dynamic_cast<Component_Timer*>(timerComp);
		if (timer == nullptr)return;
		timer->SetTime(5.f);
		timer->Start();

		Component* chaseComp = GetChildComponent("ChaseComponent");
		Component_Chase* chase = dynamic_cast<Component_Chase*>(chaseComp);
		if (chase == nullptr)return;

		chase->SetTarget(target_);
		chase->Start();

		//タイマーが終了したのであれば
		if (timer->GetIsEnd()) {

			timer->Reset();

			timer->Stop();
			chase->Stop();

			//behaviorからshootのメンバ、string pathにセットする
			//shootからbulletのメンバ、string model pathにセットする

			Component* shootcomp = GetChildComponent("ShootAttackComponent");
			Component_ShootAttack* shoot = dynamic_cast<Component_ShootAttack*>(shootcomp);
			shoot->SetBulletModelPath("Models/Enemies/Cactan/cactan.fbx");

			if (shoot == nullptr) return;
			XMFLOAT3 holderPos = holder_->GetPosition();
			XMFLOAT3 targetPos = target_->GetPosition();
			
			shoot->SetShootingDirection(XMVector3Normalize(XMLoadFloat3(&targetPos) - XMLoadFloat3(&holderPos)));
			shoot->Execute();
			shoot->Stop();

		}

	}
	else {

		Component* timecomp = GetChildComponent("TimerComponent");
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

	if (select == 0)target_ = nullptr;
	else {
		target_ = (StageObject*)holder_->FindObject(objNames[select]);

		/*	auto detector = dynamic_cast<Component_CircleRangeDetector*>(GetChildComponent("CircleRangeDetector"));
			detector->SetTarget(target_);*/
	}

#endif // _DEBUG
}

//5秒追従->止まる->撃つ->また動くの繰り返し