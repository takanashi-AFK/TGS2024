#include "RotationComponent.h"

RotationComponent::RotationComponent(StageObject* _holeder)
	:Component(_holeder,"RotationComponent",Rotation)
{
}

void RotationComponent::Initialize()
{
}

void RotationComponent::Update()
{
}

void RotationComponent::Release()
{
}

void RotationComponent::Save(json& _saveObj)
{
}

void RotationComponent::Load(json& _loadObj)
{
}

void RotationComponent::DrawData()
{
}
