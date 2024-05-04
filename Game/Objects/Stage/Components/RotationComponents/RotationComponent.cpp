#include "RotationComponent.h"

RotationComponent::RotationComponent(StageObject* _holeder)
	:Component(_holeder,"RotationComponent",Rotation)
{
}

void RotationComponent::Initialize()
{
	if (FindChildComponent(RotationX) == false)AddChildComponent(CreateComponent(RotationX, holder_));
	if (FindChildComponent(RotationY) == false)AddChildComponent(CreateComponent(RotationY, holder_));
	if (FindChildComponent(RotationZ) == false)AddChildComponent(CreateComponent(RotationZ, holder_));
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
