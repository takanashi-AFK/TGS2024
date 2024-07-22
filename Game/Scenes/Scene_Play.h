#pragma once

// �C���N���[�h
#include"../../Engine/GameObject/GameObject.h"
#include "Scene_End.h"

// �O���錾
class Component_HealthGauge;

class Scene_Play:public GameObject
{
private:
	Component_HealthGauge* playerHealth_; //�v���C���[��HP���Ǘ�����R���|�[�l���g
	Component_HealthGauge* bossHealth_; 
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

	//void ChangeState(ENDSTATE newState);
};

