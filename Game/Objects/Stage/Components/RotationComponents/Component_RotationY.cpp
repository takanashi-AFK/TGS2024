#include "Component_RotationY.h"

// �C���N���[�h
#include "../../../../../Engine/ImGui/imgui.h"
#include "../../StageObject.h"

Component_RotationY::Component_RotationY(string _name, StageObject* _holder, Component* _parent)
	:Component(_holder,_name,RotationY,_parent),angle_(0),rotateSpeed_(0)
{
}

void Component_RotationY::Initialize()
{
}

void Component_RotationY::Update()
{
	// �x���ɉ�]������
	angle_ += rotateSpeed_;

	// ��]���x�̒l�����̒l�ł��� ���� �p�x��360�x�����������A�p�x���O�ɖ߂�
	if (!std::signbit(rotateSpeed_) && angle_ >= 360.f)angle_ = 0.f;

	// ��]���x�̒l�����̒l�ł��� ���� �p�x��-360�x�����������A�p�x���O�ɖ߂�
	if (std::signbit(rotateSpeed_) && angle_ <= -360.f)angle_ = 0.f;

	// ��]���x���O�ł͂Ȃ����A�p�x��K��������
	if (rotateSpeed_ != 0.f)holder_->SetRotateY(angle_);
}

void Component_RotationY::Release()
{
}

void Component_RotationY::Save(json& _saveObj)
{
	// ��]���x��ۑ�
	_saveObj["rotateSpeed_"] = rotateSpeed_;

	// �p�x��ۑ�
	_saveObj["angle_"] = angle_;
}

void Component_RotationY::Load(json& _loadObj)
{
	// ��]���x��Ǎ�
	rotateSpeed_ = _loadObj["rotateSpeed_"];

	// �p�x��Ǎ�
	angle_ = _loadObj["angle_"];
}

void Component_RotationY::DrawData()
{
	// ��]���x��\��
	ImGui::DragFloat("rotateSpeed_", &rotateSpeed_,0.1f);
}