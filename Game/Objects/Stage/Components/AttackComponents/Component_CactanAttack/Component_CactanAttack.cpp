#include "Component_CactanAttack.h"
#include "../../../../../../Engine/ImGui/imgui.h"
Component_CactanAttack::Component_CactanAttack(StageObject* _holder):
	Component_Attack(_holder, "Component_CactanAttack", CactanAttack),pBullet(nullptr)
{
}

void Component_CactanAttack::Initialize()
{
}

void Component_CactanAttack::Update()
{
	if (isAttack_) {
		this->Attack();
		
		isAttack_ = false;
	}
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
	if(ImGui::Button("Attack"))
	Execute();
}

void Component_CactanAttack::Attack()
{
	Bullet* pBullet = Instantiate<Bullet>(holder_->GetParent());
	pBullet->Attack(holder_->GetPosition(), XMVectorSet(0, 0, 1, 0));
}