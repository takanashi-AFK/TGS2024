#include "Component_MeleeAttack.h"
#include "../../StageObject.h"
#include "../../../../../Engine/Collider/BoxCollider.h"
#include "../../Knuckle.h"
#include "../../../../../Engine/ImGui/imgui.h"
#include "../TimerComponent/Component_Timer.h"
#include "../HealthManagerComponents/Component_HealthManager.h"
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
	power_ = 20;
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

		// 移動ベクトルが0の場合、前回のベクトルを使用
		if (XMVector3Equal(forward_, XMVectorZero()))forward_ = prevFrontVec_;

		XMStoreFloat3(&front, forward_);
		
		prevFrontVec_ = forward_;

		// 位置の更新
		collider->SetCenter(front);

		if (AutoDelete(0.1f)) {

			collider->SetCenter(XMFLOAT3{ 0,0,0 });
			Stop();
		}
	}
}

void Component_MeleeAttack::Release()
{
}

void Component_MeleeAttack::DrawData()
{
	ImGui::Text("MeleeAttack");
	ImGui::DragInt("power_", &power_);
	if (ImGui::Button("Execute"))Execute();
}

bool Component_MeleeAttack::AutoDelete(float _time)
{
	auto timer = dynamic_cast<Component_Timer*>(GetChildComponent("Timer"));
	if (timer == nullptr) return false;
	timer->SetTime(_time);
	timer->Start();
	if (timer->GetIsEnd()) {	
		timer->Reset();
		return true;
	}
	return false;
}

void Component_MeleeAttack::OnCollision(GameObject* _target)
{
	// 有効でない場合は処理を行わない
	if (isActive_ == false)return;

	// ターゲットがStageObjectでない場合は処理を行わない
	StageObject* target = dynamic_cast<StageObject*>(_target);
	if (target == nullptr) return;

	// ダメージ処理
	for (auto hm : target->FindComponent(HealthManager)) {
		((Component_HealthManager*)hm)->TakeDamage(power_);
		if (((Component_HealthManager*)hm)->GetHP() == 0.f)
		_target->KillMe();
	}
}
