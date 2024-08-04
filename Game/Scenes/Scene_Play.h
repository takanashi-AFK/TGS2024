#pragma once

// �C���N���[�h
#include"../../Engine/GameObject/GameObject.h"

// �O���錾
class Stage;
class ScoreManager;
class Scene_Play :public GameObject
{
private:
	Stage* pStage_;
	ScoreManager* pScore;
public:
	//�R���X�g���N�^
	Scene_Play(GameObject* parent);

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;
};

