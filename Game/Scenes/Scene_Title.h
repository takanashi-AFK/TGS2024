#pragma once
#include"../../Engine/GameObject/GameObject.h"
class Scene_Title :public GameObject
{

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="parent"></param>
	Scene_Title(GameObject* parent);

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

