#include "Component_PlayerBehavior.h"

// インクルード
#include "../../../../../Engine/Collider/BoxCollider.h"
#include "../../StageObject.h"
#include "../../../../../Game/Objects/Stage/Components/GaugeComponents/Component_HealthGauge.h"
#include "../../../../../Engine/ImGui/imgui.h"

Component_PlayerBehavior::Component_PlayerBehavior(string _name, StageObject* _holder, Component* _parent)
	: Component(_holder, _name, PlayerBehavior,_parent)
{
}

void Component_PlayerBehavior::Initialize()
{
	// コライダーの追加
	holder_->AddCollider(new BoxCollider(XMFLOAT3(0, 0, 0), XMFLOAT3(1, 1, 1)));

	// 子コンポーネントの追加
	if (FindChildComponent("InputMove") == false)AddChildComponent(CreateComponent("InputMove", WASDInputMove, holder_, this));
	if (FindChildComponent("HealthGauge") == false)AddChildComponent(CreateComponent("HealthGauge", HealthGauge, holder_, this));
}

void Component_PlayerBehavior::Update()
{
	auto hm = dynamic_cast<Component_HealthGauge*>(GetChildComponent("HealthGauge"));

	// 進捗を0.0〜1.0の範囲で計算
	float progress = hm->GetNow() / hm->GetMax();

	// HPゲージの表示
	ImGui::ProgressBar(progress, ImVec2(0.0f, 0.0f), "Player HP");
}

void Component_PlayerBehavior::Release()
{
}

void Component_PlayerBehavior::OnCollision(GameObject* _target)
{
}
