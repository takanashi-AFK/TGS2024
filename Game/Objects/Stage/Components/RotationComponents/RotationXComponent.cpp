#include "RotationXComponent.h"

// インクルード
#include "../../StageObject.h"
#include "../../../../../Engine/ImGui/imgui.h"

RotationXComponent::RotationXComponent(StageObject* _holeder)
	:Component(_holeder,"RotationXComponent",RotationX), angle_(0), rotateSpeed_(0)
{
}

void RotationXComponent::Initialize()
{
}

void RotationXComponent::Update()
{
	// X軸に回転させる
	angle_ += rotateSpeed_;
	if (rotateSpeed_ > 0)holder_->SetRotateX(angle_);
}

void RotationXComponent::Release()
{
}

void RotationXComponent::Save(json& _saveObj)
{
	// 回転速度を保存
	_saveObj["rotateSpeed_"] = rotateSpeed_;

	// 角度を保存
	_saveObj["angle_"] = angle_;
}

void RotationXComponent::Load(json& _loadObj)
{
	// 回転速度を読込
	rotateSpeed_ = _loadObj["rotateSpeed_"];

	// 角度を読込
	angle_ = _loadObj["angle_"];
}

void RotationXComponent::DrawData()
{
	// 回転速度を表示
	ImGui::DragFloat("rotateSpeed_", &rotateSpeed_, 0.1f);
}
