#include "Component_ShootAttack.h"

// インクルード
#include "../../../../../Engine/ImGui/imgui.h"
#include "../../Bullet.h"
#include "../../Stage.h"
#include "../../../../../Engine/Global.h"

Component_ShootAttack::Component_ShootAttack(string _name, StageObject* _holder, Component* _parent) :
	Component_Attack(_holder, _name, ShootAttack, _parent), shootingSpeed_(), shootingDirection_()
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

	bulletPrefab->SetShooter(holder_);

	// 撃ち放つ速度を設定
	bulletPrefab->SetSpeed(shootingSpeed_);

	// 撃ち放つ方向を設定
	bulletPrefab->SetDirection(shootingDirection_);

	// 撃ち放つ位置を設定
	if (isShootPositionSet_ == true)bulletPrefab->SetPosition(shootingPosition_);
	else bulletPrefab->SetPosition(holder_->GetPosition());

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
	_saveObj["shootingSpeed_"] = shootingSpeed_;
	_saveObj["shootingDirection_"] = { REFERENCE_XMVECTOR3(shootingDirection_) };
}

void Component_ShootAttack::Load(json& _loadObj)
{
	if (_loadObj.contains("shootingSpeed_"))shootingSpeed_ = _loadObj["shootingSpeed_"];
	if (_loadObj.contains("shootingDirection_"))shootingDirection_ = XMVectorSet(_loadObj["shootingDirection_"][0], _loadObj["shootingDirection_"][1], _loadObj["shootingDirection_"][2], 0);
}

void Component_ShootAttack::DrawData()
{
	// 速度の設定
	ImGui::DragFloat("Speed", &shootingSpeed_, 0.1f, 0.f);

	// 方向の設定
	ImGui::DragFloat3("Direction", (float*)&shootingDirection_, 0.1f);

	// 攻撃ボタン
	if (ImGui::Button("Execute"))this->Execute();

}
