#include "Component_CactanAttack.h"
#include "../../../../../../Engine/ImGui/imgui.h"
#include "../../../Bullet.h"

Component_CactanAttack::Component_CactanAttack(StageObject* _holder):
	Component_Attack(_holder, "Component_CactanAttack", CactanAttack)
{
}

void Component_CactanAttack::Initialize()
{
}

void Component_CactanAttack::Update()
{
	if (isAttack_) {
		frame++;

		Bullet * pBullet = Instantiate<Bullet>(holder_->GetParent());
		pBullet->Attack(holder_->GetPosition(), { 0,0,1 });	
		
		//Bullet* pBullet = (Bullet*)CreateStageObject("Bullet", "Models/DebugCollision/SphereCollider.fbx", holder_->GetParent());
		//pBullet->Attack(holder_->GetPosition(), {0,0,1});
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
	ImGui::Text("%d", frame);
	if(ImGui::Button("Attack"))
	Execute();
}

