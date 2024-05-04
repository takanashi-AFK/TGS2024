#include "RotationYComponent.h"

// インクルード
#include "../../StageObject.h"
#include "../../../../../Engine/ImGui/imgui.h"

RotationYComponent::RotationYComponent(StageObject* _holeder)
	:Component(_holeder,"RotationYComponent",RotationY),angle_(0),rotateSpeed_(0)
{
}

void RotationYComponent::Initialize()
{
}

void RotationYComponent::Update()
{
	// Y軸に回転させる
	angle_ += rotateSpeed_;
	if (rotateSpeed_ > 0)holder_->SetRotateY(angle_);
}

void RotationYComponent::Release()
{
}

void RotationYComponent::Save(json& _saveObj)
{
	// 回転速度を保存
	_saveObj["rotateSpeed_"] = rotateSpeed_;

	// 角度を保存
	_saveObj["angle_"] = angle_;
}

void RotationYComponent::Load(json& _loadObj)
{
	// 回転速度を読込
	rotateSpeed_ = _loadObj["rotateSpeed_"];

	// 角度を読込
	angle_ = _loadObj["angle_"];
}

void RotationYComponent::DrawData()
{
	// 回転速度を表示
	ImGui::DragFloat("rotateSpeed_", &rotateSpeed_,0.1f);
}
