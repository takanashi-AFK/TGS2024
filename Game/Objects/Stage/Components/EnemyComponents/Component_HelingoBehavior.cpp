#include "Component_HelingoBehavior.h"

#include "../../StageObject.h"
#include "../DetectorComponents/Component_CircleRangeDetector.h"
#include "../RotationComponents/Component_RotationY.h"
#include "../TimerComponent/Component_Timer.h"
#include "../MoveComponents/Component_Fall.h"
#include "../MoveComponents/Component_Chase.h"

Component_HelingoBehavior::Component_HelingoBehavior(string _name, StageObject* _holder, Component* _parent)
	: Component(_holder, _name, HelingoBehavior,_parent)
{
}

void Component_HelingoBehavior::Initialize()
{
	if (FindChildComponent("CircleRangeDetector") == false)AddChildComponent(CreateComponent("CircleRangeDetector", CircleRangeDetector, holder_, this));
	if (FindChildComponent("Timer") == false)AddChildComponent(CreateComponent("Timer", Timer, holder_, this));
	if (FindChildComponent("Fall") == false)AddChildComponent(CreateComponent("Fall", Fall, holder_, this));
	if (FindChildComponent("Chase") == false)AddChildComponent(CreateComponent("Chase", Chase, holder_, this));
}

void Component_HelingoBehavior::Update()
{
	if (target_ == nullptr)target_ = (StageObject*)holder_->FindObject(targetName_);
	if (target_ == nullptr)return;

	auto detector = dynamic_cast<Component_CircleRangeDetector*>(GetChildComponent("CircleRangeDetector"));
	if (detector == nullptr)return;

	auto fall = dynamic_cast<Component_Fall*>(GetChildComponent("Fall"));

	// 範囲内にプレイヤーがいる場合
	if (fall->IsActived() == false && detector->IsContains()) {

		// タイマーを開始
		auto timer = dynamic_cast<Component_Timer*>(GetChildComponent("Timer"));
		if (timer == nullptr)return;

		timer->Start();

		// 追従を開始
		auto chase = dynamic_cast<Component_Chase*>(GetChildComponent("Chase"));
		if (chase == nullptr)return;

		chase->SetTarget(target_);
		chase->Start();

		detector->SetRadius(fallrange_);
		if (detector->IsContains() == true) {

			// 落下する
			
			if (fall == nullptr)return;
			chase->Stop();
			fall->Start();
		}
	}

}

void Component_HelingoBehavior::Release()
{
}

void Component_HelingoBehavior::Save(json& _saveObj)
{
}

void Component_HelingoBehavior::Load(json& _loadObj)
{
}

void Component_HelingoBehavior::DrawData()
{
}
