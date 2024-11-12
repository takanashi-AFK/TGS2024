#pragma once

#include"../../Engine/GameObject/GameObject.h"

#include "../Objects/UI/UIPanel.h"
#include "../Objects/UI/UIImage.h"

class Scene_EasingTest :public GameObject
{
public:
	/// <summary> コンストラクタ </summary>
	Scene_EasingTest(GameObject* parent);

	/// <summary> 初期化 </summary>
	void Initialize() override;

	/// <summary> 更新 </summary>
	void Update() override;

	/// <summary> 描画 </summary>
	void Draw() override;

	/// <summary> 解放 </summary>
	void Release() override;

private:

	UIImage* i_Left;
	UIImage* i_Right;

	uint16_t count_;
};

namespace Scene_EasingTestString
{
	constexpr LPCSTR BackGround = "aa";
	constexpr LPCSTR ImageRight = "imageright";
	constexpr LPCSTR ImageLeft = "imageleft";
}