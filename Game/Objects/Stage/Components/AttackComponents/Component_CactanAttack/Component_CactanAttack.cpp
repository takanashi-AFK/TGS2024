#include "Component_CactanAttack.h"
#include "../../../../../../Engine/ImGui/imgui.h"
Component_CactanAttack::Component_CactanAttack(StageObject* _holder):
	Component_Attack(_holder, "Component_CactanAttack", CactanAttack),
	frame(0)
{
}

void Component_CactanAttack::Initialize()
{
}

void Component_CactanAttack::Update()
{	

}

void Component_CactanAttack::Release()
{
}

void Component_CactanAttack::Save(json& _saveobj)
{
}

void Component_CactanAttack::Load(json& _loadobj)
{

}

void Component_CactanAttack::DrawData()
{
	XMFLOAT3 dir;
	ImGui::DragFloat("Speed", &speed_);
	XMStoreFloat3(&dir, direction_);
	ImGui::DragFloat3("Direction", &dir.x);
	direction_ = XMLoadFloat3(&dir);

	if (ImGui::Button("Attack")) {
	Bullet* pBullet = Instantiate<Bullet>(holder_->GetParent());
	pBullet->SetDirection(direction_);
	pBullet->SetSpeed(speed_);
	pBullet->SetPosition(holder_->GetPosition());
	pBullet->Execute();
	}
}

void Component_CactanAttack::Attack()
{

}