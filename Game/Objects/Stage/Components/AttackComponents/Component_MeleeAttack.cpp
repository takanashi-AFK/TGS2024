#include "Component_MeleeAttack.h"
#include "../../StageObject.h"
#include "../../../../../Engine/Collider/BoxCollider.h"
#include "../../../../../Engine/ImGui/imgui.h"
#include "../TimerComponent/Component_Timer.h"
#include "../HealthManagerComponents/Component_HealthManager.h"
#include "../../Stage.h"

Component_MeleeAttack::Component_MeleeAttack(string _name, StageObject* _holder, Component* _parent)
	:Component_Attack(_holder, _name, MeleeAttack, _parent), isHit_(false),colliderSize_(1.f,1.f,1.f)
{
}

void Component_MeleeAttack::Initialize()
{
	//タイマーの追加
	if (!FindChildComponent("Timer")) {
		AddChildComponent(CreateComponent("Timer", Timer, holder_, this));
	}

	//コライダーの追加
	holder_->AddCollider(new BoxCollider(XMFLOAT3(0, 0, 0), XMFLOAT3(1, 1, 1)));
	power_ = 20;
}

void Component_MeleeAttack::Update()
{
	// 有効でない場合は処理を行わない
	if (isActive_ == false) return;

	// コライダーの更新
	Collider* collider = dynamic_cast<BoxCollider*>(holder_->GetCollider(0));
	if (!collider) return;
	{
		//前方向の取得
		XMFLOAT3 front{};

		// 移動ベクトルが0の場合、前回のベクトルを使用
		if (XMVector3Equal(forward_, XMVectorZero())) {
			forward_ = prevFrontVec_;
		}

		XMStoreFloat3(&front, forward_);

		prevFrontVec_ = forward_;

		// 位置の更新
		collider->SetCenter(front);

		if (AutoDelete(0.03f)) {
			collider->SetCenter(XMFLOAT3{ 0, 0, 0 });
			Stop();
			isOneHit_ = false;  // AutoDeleteがtrueの場合にリセット
		}
	}
}

void Component_MeleeAttack::Release()
{
}

void Component_MeleeAttack::DrawData()
{
	// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	// 攻撃力の設定
	// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	ImGui::DragInt("power_", &power_);

	// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	// コライダーの大きさ
	// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	if (ImGui::DragFloat3("colliderSize_", (float*)&colliderSize_, 0.01f)) {
		// コライダーの大きさを変更
		BoxCollider* collider = dynamic_cast<BoxCollider*>(holder_->GetCollider(0));
		if (collider != nullptr) collider->SetSize(colliderSize_);
	}

	// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	// 攻撃方向の設定
	// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	ImGui::DragFloat3("direction_", (float*)&direction_, 0.01f);

	// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	// 実行ボタンの設定
	// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	if (ImGui::Button("Execute")) Execute();

	// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	// 近距離攻撃がヒットしたかどうか
	// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	ImGui::SameLine();
	ImGui::Text("isHit : %s",isOneHit_ ? "true" : "false");
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

void Component_MeleeAttack::OnCollision(GameObject* _target)
{
	// 有効でない場合は処理を行わない
	if (!isActive_ || isOneHit_) return;

	// ターゲットがStageObjectでない場合は処理を行わない
	StageObject* target = dynamic_cast<StageObject*>(_target);
	if (!target) return;

	// ダメージ処理
	for (auto hm : target->FindComponent(HealthManager)) {
		((Component_HealthManager*)hm)->TakeDamage(power_);
		isOneHit_ = true;  // ダメージ処理の直後にフラグを設定

		if (((Component_HealthManager*)hm)->GetHP() <= 0.f) {
			((Stage*)holder_->FindObject("Stage"))->DeleteStageObject((StageObject*)_target);
		}
	}
}
