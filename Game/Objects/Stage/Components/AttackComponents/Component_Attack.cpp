#include "Component_Attack.h"

Component_Attack::Component_Attack(StageObject* _holder) :
	Component(_holder, "Component_Attack", Attack), isAttack_(false), power_(0)
{
}

Component_Attack::Component_Attack(StageObject* _holder, string _name, ComponentType _type) :
	Component(_holder, _name, _type), isAttack_(false), power_(0)
{
}

void Component_Attack::Initialize()
{
}

void Component_Attack::Update()
{
}

void Component_Attack::Release()
{
}

void Component_Attack::Save(json& _saveobj)
{
}

void Component_Attack::Load(json& _loadobj)
{
}

void Component_Attack::DrawData()
{
}
