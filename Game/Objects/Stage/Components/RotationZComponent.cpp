#include "RotationZComponent.h"
#include "../StageObject.h"
#include "../../../../Engine/ImGui/imgui.h"

RotationZComponent::RotationZComponent(StageObject* _holeder)
	:Component(_holeder, "RotationZComponent", RotationZ), angleZ_(0), rotateSpeed_(0)
{
}

void RotationZComponent::Initialize()
{
}

void RotationZComponent::Update()
{
	angleZ_ += rotateSpeed_;
	holder_->SetRotateZ(angleZ_);
}

void RotationZComponent::Release()
{
}

void RotationZComponent::Save(json& _saveObj)
{
	_saveObj["rotateSpeed_"] = rotateSpeed_;
}

void RotationZComponent::Load(json& _loadObj)
{
	rotateSpeed_ = _loadObj["rotateSpeed_"];
}

void RotationZComponent::DrawData()
{
	ImGui::DragFloat("rotateSpeed_", &rotateSpeed_, 0.1f);
}
