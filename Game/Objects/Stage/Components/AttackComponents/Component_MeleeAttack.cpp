#include "Component_MeleeAttack.h"
#include "../../StageObject.h"
#include "../../../../../Engine/Collider/BoxCollider.h"
#include "../../Knuckle.h"
#include "../../../../../Engine/ImGui/imgui.h"
#include "../TimerComponent/Component_Timer.h"
#include "../HealthManagerComponents/Component_HealthManager.h"

namespace {
	EFFEKSEERLIB::EFKTransform t;/*★★★*/
}

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

	// effekseer: :Effectの読み込み
	EFFEKSEERLIB::gEfk->AddEffect("attack", "Effects/Attack6.efk");/*★★★*/

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
	ImGui::DragInt("shotrange_", &power_);
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

void Component_MeleeAttack::OnCollision(GameObject* _target)
{
	// 有効でない場合は処理を行わない
	if (isActive_ == false)return;

	// ターゲットがStageObjectでない場合は処理を行わない
	StageObject* target = dynamic_cast<StageObject*>(_target);
	if (target == nullptr) return;

	DirectX::XMStoreFloat4x4(&(t.matrix), holder_->GetWorldMatrix());/*★★★*/
	t.isLoop = false;/*★★★*/
	t.maxFrame = 60;/*★★★*/
	t.speed = 1.0f;/*★★★*/


	// effekseer: :Effectの再生
	mt = EFFEKSEERLIB::gEfk->Play("attack", t);/*★★★*/

	// ダメージ処理
	for (auto hm : target->FindComponent(HealthManager)) {
		((Component_HealthManager*)hm)->TakeDamage(power_);
	}

	// 終了処理
	isActive_ = false;
}
