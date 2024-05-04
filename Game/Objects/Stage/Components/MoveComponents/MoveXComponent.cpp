#include "MoveXComponent.h"

// インクルード
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
	// 現在の位置を取得
	XMFLOAT3 position = holder_->GetPosition();
	
	// 方向を決定
	XMVECTOR dir = XMVectorSet(1, 0, 0, 0);

	// 移動先を決定
	XMStoreFloat3(&position, XMLoadFloat3(&position) + XMVector3Normalize(dir) * moveSpeedX_);

	// 移動
	holder_->SetPosition(position);
}

void MoveXComponent::Release()
{
}

void MoveXComponent::Save(json& _saveObj)
{
	// 移動速度を保存
	_saveObj["moveSpeedX_"] = moveSpeedX_;
}

void MoveXComponent::Load(json& _loadObj)
{
	// 移動速度を読込
	moveSpeedX_ = _loadObj["moveSpeedX_"];
}

void MoveXComponent::DrawData()
{
	// 移動速度を編集
	ImGui::DragFloat("moveSpeedX_",&moveSpeedX_,0.1f);
	
	// 移動をリセット
	if (ImGui::Button("reset")) {
		moveSpeedX_ = 0; holder_->SetPosition(0, 0, 0);
	}
}
