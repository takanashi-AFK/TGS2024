#include "Component_CactanAttack.h"
#include "../../../../../../Engine/ImGui/imgui.h"

Component_CactanAttack::Component_CactanAttack(StageObject* _holder):
	Component_Attack(_holder, "Component_CactanAttack", CactanAttack),pBullet(nullptr)
{
}

void Component_CactanAttack::Initialize()
{
	pBullet = Instantiate<Bullet>(holder_->GetParent());
}

void Component_CactanAttack::Update()
{
	if (isAttack_) {
		frame++;

		//Bullet * pBullet = Instantiate<Bullet>(holder_->GetParent());
		//pBullet->Update(holder_->GetPosition(), {0,0,1});

		pBullet->Update(holder_->GetPosition(), {0,0,1});
		pBullet->TestAttack();
		
		//pBullet->Attack(holder_->GetPosition(), {0,0,1});
		
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

