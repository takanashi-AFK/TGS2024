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
#include "../../../../../Engine/DirectX/Direct3D.h"
#include "../../Stage.h"
#include "../../../../../Engine/GameObject/Camera.h"
#include "../TimerComponent/Component_Timer.h"

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
	if (FindChildComponent("Timer") == false)AddChildComponent(CreateComponent("Timer", Timer, holder_, this));
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

	melee->SetForward(frontVec_);

	// HPゲージの表示
	ImGui::ProgressBar(progress, ImVec2(0.0f, 0.0f), "Player HP");


	auto shoot = dynamic_cast<Component_ShootAttack*>(GetChildComponent("ShootAttack"));
	if (shoot == nullptr)return;

	auto timer = dynamic_cast<Component_Timer*>(GetChildComponent("Timer"));
	if (timer == nullptr)return;

	if (target_ == nullptr) target_ = (StageObject*)holder_->FindObject(targetName_);

	// 枠内にいるENEMY属性を持ったStageObjectをターゲットにする
	if (Input::IsMouseButton(1) && Input::IsMouseButtonDown(0))
	{

		//if (IsEnemyInRect(target_)) {
		//	XMFLOAT3 targetPos = target_->GetPosition();
		//	XMFLOAT3 holderPos = holder_->GetPosition();
		//	XMVECTOR targetVector = XMLoadFloat3(&targetPos);
		//	XMVECTOR holderVector = XMLoadFloat3(&holderPos);
		//	XMVECTOR dir = XMVector3Normalize(targetVector - holderVector);

		//	shoot->SetShootingDirection(dir);// targetを取得、方向指定	
		//}
		//else 
		shoot->SetShootingDirection(Camera::GetSightLine());
			
		shoot->SetShootingSpeed(2.f);
		shoot->Execute();
	}
	else if(Input::IsMouseButtonDown(0))
	{
		melee->Execute();
	}
}

void Component_PlayerBehavior::Release()
{
}

void Component_PlayerBehavior::DrawData()
{
	 ImGui::Text("%f,%f,%f,%f", frontVec_.m128_f32);
	 auto timer = dynamic_cast<Component_Timer*>(GetChildComponent("Timer"));
	 if (timer == nullptr)return;
	 ImGui::Text("%f", timer->GetNowTime());
}

void Component_PlayerBehavior::OnCollision(GameObject* _target)
{
}

//bool Component_PlayerBehavior::IsEnemyInRect(StageObject* _target)
//{
//
//	if (_target == nullptr) return false;
//	XMFLOAT3 pos = ConvertTo2DPos(_target);
//
//	float left = -0.8f;    // 左の境界
//	float right = 0.8f;    // 右の境界
//	float top = 0.8f;      // 上の境界
//	float bottom = -0.8f;  // 下の境界
//	if (_target->GetAttribute() == ENEMY && pos.x <= left && pos.x >= right && pos.y <= bottom && pos.y >= top)
//		return true;
//	
//	return false;
//
//}
//
//XMFLOAT3 Component_PlayerBehavior::ConvertTo2DPos(StageObject* _target)
//{
//	int scWidth = Direct3D::screenWidth_;
//	int scHeight = Direct3D::screenHeight_;
//
//#ifdef _DEBUG
//	scWidth = scWidth * 0.7;
//	scHeight = scHeight * 0.7;
//#endif // _DEBUG
//
//	XMFLOAT3 targetPos = _target->GetPosition();
//
//	targetPos.x = (float)(targetPos.x * 2.0f) / (float)scWidth - 1.0f;
//	targetPos.y = 1.0f - (float)(targetPos.y * 2.0f) / (float)scHeight;
//	targetPos.z = 0.0f;
//
//	return targetPos;
//}
