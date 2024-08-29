#include "Component_Guard.h"


Component_Guard::Component_Guard(string _name, StageObject* _holder, Component* _parent):
	Component(_holder, _name,Guard, _parent)
{
}

void Component_Guard::Initialize()
{
}

void Component_Guard::Update()
{
	if (isActive_) {

	}
}

void Component_Guard::Release()
{
}

void Component_Guard::Save(json& _saveObj)
{
}

void Component_Guard::Load(json& _loadObj)
{
}

void Component_Guard::DrawData()
{
}
