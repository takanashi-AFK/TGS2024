#include "Component_CactanBehavior.h"
#include "../TimerComponent/Component_Timer.h"
#include "../AttackComponents/Component_ShootAttack.h"
#include "../DetectorComponents/Component_CircleRangeDetector.h"

Component_CactanBehavior::Component_CactanBehavior(string _name, StageObject* _holder, Component* _parent)
	:Component(_holder, _name, CactanBihavior, _parent)
{
}

void Component_CactanBehavior::Initialize()
{
	// 必要なコンポーネントを追加
	if (FindChildComponent("CircleRangeDetector") == false)AddChildComponent(CreateComponent("CircleRangeDetector",CircleRangeDetector,holder_,this));
	if (FindChildComponent("ShootAttack") == false)AddChildComponent(CreateComponent("ShootAttack", ShootAttack, holder_, this));
	if (FindChildComponent("Timer") == false)AddChildComponent(CreateComponent("Timer", Timer, holder_, this));
}

void Component_CactanBehavior::Update()
{
	auto detector = dynamic_cast<Component_CircleRangeDetector*>(GetChildComponent("CircleRangeDetector"));
	if (detector == nullptr)return;

	// 範囲内にプレイヤーがいる場合
	if (detector->IsContains())
	{
		// タイマーを開始
		auto timer = dynamic_cast<Component_Timer*>(GetChildComponent("Timer"));
		if (timer == nullptr)return;

		timer->Start();
		if (timer->IsIntervalTime(3.f))
		{
			// シュートアタックを開始
			auto shoot = dynamic_cast<Component_ShootAttack*>(GetChildComponent("ShootAttack"));
			if (shoot == nullptr)return;
			shoot->Execute();
		}
	}
	else
	{
		// タイマーを停止
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
}

void Component_CactanBehavior::Load(json& _loadObj)
{
}

void Component_CactanBehavior::DrawData()
{
}
