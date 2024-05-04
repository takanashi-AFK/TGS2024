#include "RotationXComponent.h"
#include "../../StageObject.h"
#include "../../../../../Engine/ImGui/imgui.h"
RotationXComponent::RotationXComponent(StageObject* _holeder)
	:Component(_holeder,"RotationXComponent",RotationX), angleX_(0), rotateSpeed_(0)
{
}

void RotationXComponent::Initialize()
{
}

void RotationXComponent::Update()
{
	angleX_ += rotateSpeed_;
	holder_->SetRotateX(angleX_);
}

void RotationXComponent::Release()
{
}

void RotationXComponent::Save(json& _saveObj)
{
	_saveObj["rotateSpeed_"] = rotateSpeed_;
}

void RotationXComponent::Load(json& _loadObj)
{
	rotateSpeed_ = _loadObj["rotateSpeed_"];
}

void RotationXComponent::DrawData()
{
	ImGui::DragFloat("rotateSpeed_", &rotateSpeed_, 0.1f);
}
