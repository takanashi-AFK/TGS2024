#pragma once
#include"../../Engine/GameObject/GameObject.h"
class Scene_Splash :public GameObject
{
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="parent"></param>
	Scene_Splash(GameObject* parent);

	/// <summary>
	/// ������
	/// </summary>
	void Initialize() override;

	/// <summary>
	/// �X�V
	/// </summary>
	void Update() override;

	/// <summary>
	/// �`��
	/// </summary>
	void Draw() override;

	/// <summary>
	/// �J��
	/// </summary>
	void Release() override;
};

