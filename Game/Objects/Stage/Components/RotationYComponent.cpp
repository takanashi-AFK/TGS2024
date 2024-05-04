#include "RotationYComponent.h"
#include "../StageObject.h"
#include "../../../../Engine/ImGui/imgui.h"

RotationYComponent::RotationYComponent(StageObject* _holeder)
	:Component(_holeder,"RotationYComponent",RotationY),angleY_(0),rotateSpeed_(0)
{
}

void RotationYComponent::Initialize()
{
}

void RotationYComponent::Update()
{
	angleY_ += rotateSpeed_;
	holder_->SetRotateY(angleY_);
}

void RotationYComponent::Release()
{
}

void RotationYComponent::Save(json& _saveObj)
{
	_saveObj["rotateSpeed_"] = rotateSpeed_;
}

void RotationYComponent::Load(json& _loadObj)
{
	rotateSpeed_ = _loadObj["rotateSpeed_"];
}

void RotationYComponent::DrawData()
{
	ImGui::DragFloat("rotateSpeed_", &rotateSpeed_,0.1f);
}
