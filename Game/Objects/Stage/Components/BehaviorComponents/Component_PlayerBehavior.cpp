#include "Component_PlayerBehavior.h"

// インクルード
#include "../../../../../Engine/Collider/BoxCollider.h"
#include "../../StageObject.h"
#include "../HealthManagerComponents/Component_HealthManager.h"
#include "../../../../../Engine/ImGui/imgui.h"
#include "../../../../../Engine/DirectX/Input.h"
#include "../MoveComponents/Component_WASDInputMove.h"
#include "../AttackComponents/Component_MeleeAttack.h"

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
	if (FindChildComponent("HealthManager") == false)AddChildComponent(CreateComponent("HealthManager", HealthManager, holder_, this));
	if (FindChildComponent("MeleeAttack") == false)AddChildComponent(CreateComponent("MeleeAttack", MeleeAttack, holder_, this));
	if (FindChildComponent("InputMove") == false)AddChildComponent(CreateComponent("InputMove", WASDInputMove, holder_, this));
}

void Component_PlayerBehavior::Update()
{
	auto hm = dynamic_cast<Component_HealthManager*>(GetChildComponent("HealthManager"));
	if (hm == nullptr)return;

	// 進捗を0.0〜1.0の範囲で計算
	float progress = hm->GetHP() / hm->GetMax();

	auto move = dynamic_cast<Component_WASDInputMove*>(GetChildComponent("InputMove"));
	if (move == nullptr)return;
	XMFLOAT3 pos = holder_->GetPosition();

	XMVECTOR posVector = XMLoadFloat3(&pos);

	// 移動方向ベクトルを正規化
	frontVec_ = XMVector3Normalize(frontVec_);

	// 距離を掛ける (例えば 2 ユニット)
	XMVECTOR offsetVec = frontVec_ * 2.0f;

	// 現在位置に移動方向ベクトルを足す
	XMVECTOR newPosVector = posVector + offsetVec;

	// 新しい位置を XMFLOAT3 に格納
	XMStoreFloat3(&pos, newPosVector);
	
	auto melee = dynamic_cast<Component_MeleeAttack*>(GetChildComponent("MeleeAttack"));
	if (melee == nullptr)return;

	frontVec_ = move->GetMoveDirction();

	if (XMVector3Equal(frontVec_, XMVectorZero())) {
		frontVec_ = prevFrontVec_;
	}

	melee->SetForward(frontVec_);// プレイヤーの座標を取得、frontvec*2を掛けて座標を設定
	melee->Execute();


	// HPゲージの表示
	ImGui::ProgressBar(progress, ImVec2(0.0f, 0.0f), "Player HP");

	prevFrontVec_ = frontVec_;
}

void Component_PlayerBehavior::Release()
{
}

void Component_PlayerBehavior::DrawData()
{
	 ImGui::Text("%f,%f,%f,%f", frontVec_.m128_f32);
	
}

void Component_PlayerBehavior::OnCollision(GameObject* _target)
{
}
