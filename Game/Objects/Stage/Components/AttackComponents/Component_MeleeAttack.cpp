#include "Component_MeleeAttack.h"
#include "../../StageObject.h"
#include "../../../../../Engine/Collider/BoxCollider.h"
#include "../../../../../Engine/ImGui/imgui.h"
#include "../TimerComponent/Component_Timer.h"
#include "../GaugeComponents/Component_HealthGauge.h"
#include "../../Stage.h"

Component_MeleeAttack::Component_MeleeAttack(string _name, StageObject* _holder, Component* _parent)
	:Component_Attack(_holder, _name, MeleeAttack, _parent), isHit_(false), colliderSize_(1.f, 1.f, 1.f)
{
}

void Component_MeleeAttack::Initialize()
{
	// コンポーネントを追加
	if (FindChildComponent("Timer") == false) AddChildComponent(CreateComponent("Timer", Timer, holder_, this));

	//コライダーの追加
	holder_->AddCollider(new BoxCollider(XMFLOAT3(0, 0, 0), XMFLOAT3(1, 1, 1)));
}

void Component_MeleeAttack::Update()
{
	// タイマーを取得
	auto timer = dynamic_cast<Component_Timer*>(GetChildComponent("Timer"));
	if (timer == nullptr) return;

	// 有効でない場合は処理を行わない
	if (isActive_ == false) {
		timer->Reset();
		timer->SetTime(0.03f);
		return;
	}

	// タイマーを開始
	timer->Start();

	// コライダーを取得
	Collider* collider = dynamic_cast<BoxCollider*>(holder_->GetCollider(0));
	
	// コライダーが取得できない場合は処理を行わない
	if (collider == nullptr) return;

	// holderの位置と攻撃方向から、コライダーの位置を設定
	{
		// 保有者の位置に攻撃方向を加算
		XMFLOAT3 pos;
		XMStoreFloat3(&pos,XMVector3Normalize(direction_));

		// コライダーの位置を設定
		collider->SetCenter(pos);
	}

	// タイマーが終了している場合は、攻撃を終了
	if (timer->GetIsEnd() == true) {
		Stop();
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
	ImGui::Text("isHit : %s",isHit_ ? "true" : "false");

	// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	// アクティブ状態かどうかの設定
	// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	ImGui::Text("isActive_ : %s", isActive_ ? "true" : "false");

}

void Component_MeleeAttack::OnCollision(GameObject* _target)
{
	// 有効でない場合は処理を行わない
	if (!isActive_ || isHit_) return;

	// ターゲットがStageObjectでない場合は処理を行わない
	StageObject* target = dynamic_cast<StageObject*>(_target);
	if (target == nullptr) return;

	// ダメージ処理
	for (auto hm : target->FindComponent(HealthGauge)) {
		((Component_HealthGauge*)hm)->TakeDamage(power_);
		isHit_ = true;  // ダメージ処理の直後にフラグを設定

		if (((Component_HealthGauge*)hm)->GetNow() <= 0.f) {
			((Stage*)holder_->FindObject("Stage"))->DeleteStageObject((StageObject*)_target);
		}
	}
}
