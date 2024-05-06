#include "Component_RotationZ.h"

// インクルード
#include "../../StageObject.h"
#include "../../../../../Engine/ImGui/imgui.h"

Component_RotationZ::Component_RotationZ(StageObject* _holeder)
	:Component(_holeder, "Component_RotationZ", RotationZ), angle_(0), rotateSpeed_(0)
{
}

void Component_RotationZ::Initialize()
{
}

void Component_RotationZ::Update()
{
	// Z軸に回転させる
	angle_ += rotateSpeed_;

	// 回転速度の値が正の値である かつ 角度が360度を上回った時、角度を０に戻す
	if (!std::signbit(rotateSpeed_) && angle_ >= 360.f)angle_ = 0.f;

	// 回転速度の値が負の値である かつ 角度が-360度を上回った時、角度を０に戻す
	if (std::signbit(rotateSpeed_) && angle_ <= -360.f)angle_ = 0.f;

	// 回転速度が０ではない時、角度を適応させる
	if (rotateSpeed_ != 0.f)holder_->SetRotateZ(angle_);
}

void Component_RotationZ::Release()
{
}

void Component_RotationZ::Save(json& _saveObj)
{
	// 回転速度を保存
	_saveObj["rotateSpeed_"] = rotateSpeed_;

	// 角度を保存
	_saveObj["angle_"] = angle_;
}

void Component_RotationZ::Load(json& _loadObj)
{
	// 回転速度を読込
	rotateSpeed_ = _loadObj["rotateSpeed_"];

	// 角度を読込
	angle_ = _loadObj["angle_"];
}

void Component_RotationZ::DrawData()
{
	// 回転速度を編集
	ImGui::DragFloat("rotateSpeed_", &rotateSpeed_, 0.1f);
}
