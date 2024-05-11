#include "Component_Rotation.h"

Component_Rotation::Component_Rotation(StageObject* _holder)
	:Component(_holder,"Component_Rotation",Rotation)
{
}

void Component_Rotation::Initialize()
{
	// 各軸の回転用コンポーネントを追加
	if (FindChildComponent(RotationX) == false)AddChildComponent(CreateComponent(RotationX, holder_));
	if (FindChildComponent(RotationY) == false)AddChildComponent(CreateComponent(RotationY, holder_));
	if (FindChildComponent(RotationZ) == false)AddChildComponent(CreateComponent(RotationZ, holder_));
}

void Component_Rotation::Update()
{
}

void Component_Rotation::Release()
{
}

void Component_Rotation::Save(json& _saveObj)
{
}

void Component_Rotation::Load(json& _loadObj)
{
}

void Component_Rotation::DrawData()
{
}
