#include "TestObject_Plane.h"

#include "Engine/ResourceManager/Model.h"

TestObject_Plane::TestObject_Plane(GameObject* _parent)
	:GameObject(_parent,"TestObject_Plane")
{
}

void TestObject_Plane::Initialize()
{
	modelHandle_ = Model::Load("Models/tile.fbx");
	assert(modelHandle_ >= 0);
}

void TestObject_Plane::Update()
{
}

void TestObject_Plane::Draw()
{
	Model::SetTransform(modelHandle_, transform_);
	Model::Draw(modelHandle_);
}

void TestObject_Plane::Release()
{
}
