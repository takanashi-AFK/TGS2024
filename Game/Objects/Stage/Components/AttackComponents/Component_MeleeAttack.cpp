#include "Component_MeleeAttack.h"
#include "../../StageObject.h"
#include "../../../../../Engine/Collider/BoxCollider.h"
#include "../../Knuckle.h"
#include "../../../../../Engine/ImGui/imgui.h"
#include "../TimerComponent/Component_Timer.h"
Component_MeleeAttack::Component_MeleeAttack(string _name, StageObject* _holder, Component* _parent)
	:Component_Attack(_holder, _name, MeleeAttack, _parent), collider_(nullptr)
{
}

void Component_MeleeAttack::Initialize()
{
	if (FindChildComponent("Timer") == false)AddChildComponent(CreateComponent("Timer", Timer, holder_, this));
	
}

void Component_MeleeAttack::Update()
{
	if (isActive_) {
		collider_ = new BoxCollider(colliderPos_, XMFLOAT3(1, 1, 1));
		holder_->AddCollider(collider_);
		isActive_ = false;
	}
	AutoDelete(1.f);
}

void Component_MeleeAttack::Release()
{
}

void Component_MeleeAttack::DrawData()
{
	ImGui::Text("MeleeAttack");
	if (ImGui::Button("Execute"))Execute();

	ImGui::Text("%f,%f,%f", colliderPos_);

}

void Component_MeleeAttack::AutoDelete(float _time)
{
	if (collider_ == nullptr)return;
	auto timer = dynamic_cast<Component_Timer*>(GetChildComponent("Timer"));
	if (timer == nullptr) return;
	timer->SetTime(_time);
	timer->Start();
	if (timer->GetIsEnd()) {
		holder_->ClearCollider();
		collider_ = nullptr;
		timer->Reset();
	}
}
