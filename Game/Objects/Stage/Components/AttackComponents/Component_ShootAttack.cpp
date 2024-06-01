#include "Component_ShootAttack.h"

// インクルード
#include "../../../../../Engine/ImGui/imgui.h"
#include "../../Bullet.h"
#include "../../Stage.h"

Component_ShootAttack::Component_ShootAttack(string _name, StageObject* _holder, Component* _parent):
	Component_Attack(_holder, _name, ShootAttack,_parent),
	bulletSpeed_(0.5f)
{
}

void Component_ShootAttack::Initialize()
{
}

void Component_ShootAttack::Update()
{	
	if (isActive_ == false)return;

	// 撃ち放つプレハブを生成
	Bullet* bulletPrefab = Instantiate<Bullet>(holder_->GetParent());
	
	// 撃ち放つ速度を設定
	bulletPrefab->SetSpeed(bulletSpeed_);

	// 撃ち放つ方向を設定
	bulletPrefab->SetDirection(bulletDirection_);

	// 撃ち放つ位置を設定
	bulletPrefab->SetPosition(holder_->GetPosition());

	// 撃ち放つ
	bulletPrefab->Execute();
	
	// 攻撃を停止
	Stop();
}

void Component_ShootAttack::Release()
{
}

void Component_ShootAttack::Save(json& _saveObj)
{
}

void Component_ShootAttack::Load(json& _loadObj)
{
}

void Component_ShootAttack::DrawData()
{
	// 速度の設定
	ImGui::DragFloat("Speed", &bulletSpeed_, 0.1f, 0, 2.f);
	
	// 方向の設定
	ImGui::DragFloat3("Direction", (float*)&bulletDirection_, 0.1f);

	// 攻撃ボタン
	if (ImGui::Button("Execute"))this->Execute();
}
