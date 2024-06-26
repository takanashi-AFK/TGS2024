#include "Component_PlayerBehavior.h"

// インクルード
#include "../../../../../Engine/Collider/BoxCollider.h"
#include "../../../../../Engine/DirectX/Input.h"
#include "../../../../../Engine/ImGui/imgui.h"
#include "../../StageObject.h"
#include "../AttackComponents/Component_MeleeAttack.h"
#include "../AttackComponents/Component_ShootAttack.h"
#include "../HealthManagerComponents/Component_HealthManager.h"
#include "../MoveComponents/Component_WASDInputMove.h"

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
	if (FindChildComponent("ShootAttack") == false)AddChildComponent(CreateComponent("ShootAttack", ShootAttack, holder_, this));
}

void Component_PlayerBehavior::Update()
{
	auto hm = dynamic_cast<Component_HealthManager*>(GetChildComponent("HealthManager"));
	if (hm == nullptr)return;

	// 進捗を0.0〜1.0の範囲で計算
	float progress = hm->GetHP() / hm->GetMax();

	auto move = dynamic_cast<Component_WASDInputMove*>(GetChildComponent("InputMove"));
	if (move == nullptr)return;
	auto melee = dynamic_cast<Component_MeleeAttack*>(GetChildComponent("MeleeAttack"));
	if (melee == nullptr)return;

	frontVec_ = move->GetMoveDirction();

	// 移動ベクトルが0の場合、前回のベクトルを使用
	if (XMVector3Equal(frontVec_, XMVectorZero()))frontVec_ = prevFrontVec_;

	
	melee->SetForward(frontVec_);
	melee->Execute();


	// HPゲージの表示
	ImGui::ProgressBar(progress, ImVec2(0.0f, 0.0f), "Player HP");

	prevFrontVec_ = frontVec_;

	//auto shoot = dynamic_cast<Component_ShootAttack*>(GetChildComponent("ShootAttack"));
	//if (shoot == nullptr)return;
	//if (Input::IsMouseButtonDown(1)&&Input::IsMouseButtonDown(0))
	//{

	//	if (true/*二次元座標化した枠内に敵がいたら*/) shoot->SetShootingDirection(frontVec_);// targetを取得、方向指定	
	//	else shoot->SetShootingDirection(frontVec_);
	//		
	//	
	//	shoot->SetShootingSpeed(2.f);

	//	shoot->Execute();
	//}

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
