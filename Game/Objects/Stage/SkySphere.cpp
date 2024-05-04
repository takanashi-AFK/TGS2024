#include "SkySphere.h"

// インクルード
#include "../../../Engine/ResourceManager/Model.h"
#include "../../../Engine/DirectX/Direct3D.h"

SkySphere::SkySphere(GameObject* _parent)
	:StageObject("SkySphere", "Models/SkySphere/SkySphere.fbx", _parent)
{
}

void SkySphere::Initialize()
{
	// モデルの読み込み
	modelHandle_ = Model::Load(modelFilePath_);
	assert(modelHandle_ >= 0);

	// 保有するコンポーネントの初期化処理
	for (auto comp : myComponents_)comp->ChildIntialize();
}

void SkySphere::Draw()
{
	// スカイスフィア用のシェーダーを設定
	Direct3D::SetShader(Direct3D::SHADER_SKY);

	// モデルの描画
	Model::SetTransform(modelHandle_, transform_);
	Model::Draw(modelHandle_);

	// シェーダーを元に戻す
	Direct3D::SetShader(Direct3D::SHADER_3D);
}
