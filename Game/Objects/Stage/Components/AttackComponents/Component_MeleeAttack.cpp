#include "Component_MeleeAttack.h"
#include "../../StageObject.h"
#include "../../../../../Engine/Collider/BoxCollider.h"
#include "../../../../../Engine/ImGui/imgui.h"
#include "../TimerComponent/Component_Timer.h"
#include "../GaugeComponents/Component_HealthGauge.h"
#include "../../Stage.h"

Component_MeleeAttack::Component_MeleeAttack(string _name, StageObject* _holder, Component* _parent)
	:Component_Attack(_holder, _name, MeleeAttack, _parent), isHit_(false)
{
}

void Component_MeleeAttack::Initialize()
{

	if (!FindChildComponent("Timer")) {
		AddChildComponent(CreateComponent("Timer", Timer, holder_, this));
	}

	holder_->AddCollider(new BoxCollider(XMFLOAT3(0, 0, 0), XMFLOAT3(1, 1, 1)));
	power_ = 20;
}

void Component_MeleeAttack::Update()
{

	if (!isActive_) return;


	Collider* collider = dynamic_cast<BoxCollider*>(holder_->GetCollider(0));
	if (!collider) return;

	{
		XMFLOAT3 front{};

		// 正面ベクトルがなかったら
		if (XMVector3Equal(forward_, XMVectorZero())) {

			// 前回の正面ベクトルを使う
			forward_ = prevFrontVec_;
			if (XMVector3Equal(prevFrontVec_, XMVectorZero())) {
				forward_ = XMVectorSet(0, 0, 1, 0);	// 初期値

			}
		}

		// 正面ベクトルを取得
		XMStoreFloat3(&front, forward_);


		prevFrontVec_ = forward_;

		// 正面ベクトルを使ってコライダーの中心を更新
		collider->SetCenter(front);

		// 時間がたったら中心に戻す
		if (AutoDelete(0.03f)) {
			collider->SetCenter(XMFLOAT3{ 0, 0, 0 });
			Stop();
			isHit_ = false;
		}
	}
}

void Component_MeleeAttack::Release()
{
}

void Component_MeleeAttack::DrawData()
{
	ImGui::Text(isHit_ ? "true" : "false");

	ImGui::DragInt("power_", &power_);
	if (ImGui::Button("Execute")) Execute();
}

bool Component_MeleeAttack::AutoDelete(float _time)
{
	auto timer = dynamic_cast<Component_Timer*>(GetChildComponent("Timer"));
	if (!timer) return false;
	timer->SetTime(_time);
	timer->Start();
	if (timer->GetIsEnd()) {
		timer->Reset();
		return true;
	}
	return false;
}

void Component_MeleeAttack::OnCollision(GameObject* _target, Collider* _collider)
{
	if (!isActive_ || isHit_) return;

	StageObject* target = dynamic_cast<StageObject*>(_target);
	if (!target) return;

	for (auto hm : target->FindComponent(HealthGauge)) {
		((Component_HealthGauge*)hm)->TakeDamage(power_);
		isHit_ = true;

		if (((Component_HealthGauge*)hm)->GetNow() <= 0.f) {
			((Stage*)holder_->FindObject("Stage"))->DeleteStageObject((StageObject*)_target);
		}
	}
}