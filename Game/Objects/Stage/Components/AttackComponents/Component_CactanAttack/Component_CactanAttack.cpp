#include "Component_CactanAttack.h"
#include "../../../../../../Engine/ImGui/imgui.h"

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

		//‚±‚±‚ÉUŒ‚ˆ—‚ğ‘‚­
	}
	else {
		//I‚í‚Á‚½‚çisAttack_‚ğfalse‚É‚·‚é
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

void Component_CactanAttack::Attack(XMFLOAT3 _playerPosition, XMVECTOR direction)
{
	transform_.position_ = _playerPos;
}

