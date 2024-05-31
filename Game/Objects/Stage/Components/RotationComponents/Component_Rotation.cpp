#include "Component_Rotation.h"

Component_Rotation::Component_Rotation(string _name, StageObject* _holder, Component* _parent)
	:Component(_holder,_name,Rotation,_parent)
{
}

void Component_Rotation::Initialize()
{
	// 各軸の回転用コンポーネントを追加
	if (FindChildComponent("rotate_x") == false)AddChildComponent(CreateComponent("rotate_x", RotationX, holder_,this));
	if (FindChildComponent("rotate_y") == false)AddChildComponent(CreateComponent("rotate_y", RotationY, holder_,this));
	if (FindChildComponent("rotate_z") == false)AddChildComponent(CreateComponent("rotate_z", RotationZ, holder_,this));
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
