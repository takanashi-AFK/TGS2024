#include "Component_BossFall.h"
#include "../MoveComponents/Component_Fall.h"
#include "../MoveComponents/Component_Rise.h"
#include "../TimerComponent/Component_Timer.h"
#include "../../../../../Engine/ImGui/imgui.h"
Component_BossFall::Component_BossFall(string _name, StageObject* _holder, Component* _parent)
	:Component(_holder, _name, BossFall, _parent), nowState_(WAIT), prevState_(FALL), isActive_(false)
	, isEnd_(false)
{
}

void Component_BossFall::Initialize()
{
	if (!FindChildComponent("Rise")) AddChildComponent(CreateComponent("Rise", Rise, holder_, this));
	if (!FindChildComponent("Fall")) AddChildComponent(CreateComponent("Fall", Fall, holder_, this));
	if (!FindChildComponent("Timer")) AddChildComponent(CreateComponent("Timer", Timer, holder_, this));
}

void Component_BossFall::Update()
{
	if (!isActive_) return;
	auto rise = dynamic_cast<Component_Rise*>(GetChildComponent("Rise"));
	if (rise == nullptr) return;

	auto fall = dynamic_cast<Component_Fall*>(GetChildComponent("Fall"));
	if (fall == nullptr) return;

	auto timer = dynamic_cast<Component_Timer*>(GetChildComponent("Timer"));
	if (timer == nullptr) return;

	switch (nowState_)
	{
	case FALL:
		fall->Execute();
		if (fall->GetIsEnd()) {

			SetState(WAIT);
			prevState_ = FALL;
			isEnd_ = true;
			Stop();
		}
		break;	// 降下中の処理

	case RISE:
		rise->Execute();
		if (rise->IsEnd()) {
			timer->Reset();
			prevState_ = RISE;
			SetState(WAIT);
		}
		break;	// 上昇中の処理
	case WAIT:
		Wait();	 break;	// 待機中の処理
	}
}

void Component_BossFall::Wait()
{
	// タイマーを取得
	auto timer = dynamic_cast<Component_Timer*>(GetChildComponent("Timer"));

	if (prevState_ == FALL) {
		prevState_ = WAIT;
		SetState(RISE);
	}

	else if (prevState_ == RISE) {

		// タイマーを開始
		timer->SetTime(2.f);
		timer->Start();

		auto fall = dynamic_cast<Component_Fall*>(GetChildComponent("Fall"));
		if (fall == nullptr) return;

		fall->SetIsEnd(false);
		// タイマーが終了したら、降下状態に遷移
		if (timer->GetIsEnd())
			SetState(FALL);
	}

	float time = timer->GetNowTime();
}

void Component_BossFall::Release()
{
}

void Component_BossFall::Save(json& _saveObj)
{
}
	
void Component_BossFall::Load(json& _loadObj)
{
}

void Component_BossFall::DrawData()
{
	ImGui::Text("BossFall");
	ImGui::Text("State : %d", nowState_);

	if (ImGui::Button("Exe")) {
		Execute();
	}
}

