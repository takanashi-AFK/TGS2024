#include "TestObject_Box.h"

#include "Engine/ResourceManager/Model.h"
#include "Engine/ImGui/imgui.h"
#include "Engine/DirectX/Direct3D.h"

TestObject_Box::TestObject_Box(GameObject* _parent)
	:GameObject(_parent,"TestObject_Box")
{
}

void TestObject_Box::Initialize()
{
	modelHandle_ = Model::Load("Models/player.fbx");
	assert(modelHandle_ >= 0);
}

void TestObject_Box::Update()
{
	ImGui::Text("TestObject_Box");
	ImGui::DragFloat3("p", &transform_.position_.x, 0.1f);
	ImGui::DragFloat3("r", &transform_.rotate_.x, 1.f);
	ImGui::DragFloat3("s", &transform_.scale_.x, 0.1f);
	ImGui::Separator();
}

void TestObject_Box::Draw()
{
	Model::SetTransform(modelHandle_, transform_);
	Model::Draw(modelHandle_);

	Direct3D::SetShader(Direct3D::SHADER_SHADOW);

	Model::SetTransform(modelHandle_, transform_);
	Model::Draw(modelHandle_);
	Direct3D::SetShader(Direct3D::SHADER_3D);
}

void TestObject_Box::Release()
{
}
