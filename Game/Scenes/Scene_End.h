#pragma once
#include"../../Engine/GameObject/GameObject.h"


class Scene_End :public GameObject
{
public:
	//�R���X�g���N�^
	Scene_End(GameObject* parent_);

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;

};
