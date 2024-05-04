#include "MoveXComponent.h"
#include "../../StageObject.h"
#include "../../../../../Engine/ImGui/imgui.h"

MoveXComponent::MoveXComponent(StageObject* _holeder)
	:Component(_holeder,"MoveXComponent",MoveX),moveSpeedX_(0)
{
}

void MoveXComponent::Initialize()
{
}

void MoveXComponent::Update()
{
	// Œ»Ý‚ÌˆÊ’u‚ðŽæ“¾
	XMFLOAT3 position = holder_->GetPosition();
	
	// •ûŒü‚ðŒˆ’è
	XMVECTOR dir = XMVectorSet(1, 0, 0, 0);

	// ˆÚ“®æ‚ðŒˆ’è
	XMStoreFloat3(&position, XMLoadFloat3(&position) + XMVector3Normalize(dir) * moveSpeedX_);

	// ˆÚ“®
	holder_->SetPosition(position);
}

void MoveXComponent::Release()
{
}

void MoveXComponent::Save(json& _saveObj)
{
	_saveObj["moveSpeedX_"] = moveSpeedX_;
}

void MoveXComponent::Load(json& _loadObj)
{
	moveSpeedX_ = _loadObj["moveSpeedX_"];
}

void MoveXComponent::DrawData()
{
	ImGui::DragFloat("moveSpeedX_",&moveSpeedX_,0.1f);
	if (ImGui::Button("reset")) {
		moveSpeedX_ = 0; holder_->SetPosition(0, 0, 0);
	}
}
