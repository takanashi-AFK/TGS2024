#pragma once

#include"../../Engine/GameObject/GameObject.h"

#include "../Objects/UI/UIPanel.h"
#include "../Objects/UI/UIImage.h"

class Scene_EasingTest :public GameObject
{
public:
	/// <summary> �R���X�g���N�^ </summary>
	Scene_EasingTest(GameObject* parent);

	/// <summary> ������ </summary>
	void Initialize() override;

	/// <summary> �X�V </summary>
	void Update() override;

	/// <summary> �`�� </summary>
	void Draw() override;

	/// <summary> ��� </summary>
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