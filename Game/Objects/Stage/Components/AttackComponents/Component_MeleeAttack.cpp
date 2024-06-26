#include "Component_MeleeAttack.h"
#include "../../StageObject.h"
#include "../../../../../Engine/Collider/BoxCollider.h"
#include "../../Knuckle.h"
#include "../../../../../Engine/ImGui/imgui.h"
#include "../TimerComponent/Component_Timer.h"
Component_MeleeAttack::Component_MeleeAttack(string _name, StageObject* _holder, Component* _parent)
	:Component_Attack(_holder, _name, MeleeAttack, _parent)
{
}

void Component_MeleeAttack::Initialize()
{
	//タイマーの追加
	if (FindChildComponent("Timer") == false)AddChildComponent(CreateComponent("Timer", Timer, holder_, this));
	
	//コライダーの追加
	holder_->AddCollider(new BoxCollider(XMFLOAT3(0, 0, 0), XMFLOAT3(1, 1, 1)));
}

void Component_MeleeAttack::Update()
{
	// 有効でない場合は処理を行わない
	if (isActive_ == false)return;

	// コライダーの更新
	Collider* collider = dynamic_cast<BoxCollider*>((holder_->GetCollider(0)));
	if (collider == nullptr) return;
	{
		//前方向の取得
		XMFLOAT3 front{};
		XMStoreFloat3(&front, forward_);
		
		// 位置の更新
		collider->SetCenter(front);
	}
}

void Component_MeleeAttack::Release()
{
}

void Component_MeleeAttack::DrawData()
{
	ImGui::Text("MeleeAttack");
	if (ImGui::Button("Execute"))Execute();
}

void Component_MeleeAttack::AutoDelete(float _time)
{
	auto timer = dynamic_cast<Component_Timer*>(GetChildComponent("Timer"));
	if (timer == nullptr) return;
	timer->SetTime(_time);
	timer->Start();
	if (timer->GetIsEnd()) {
		holder_->ClearCollider();
		timer->Reset();
	}
}
