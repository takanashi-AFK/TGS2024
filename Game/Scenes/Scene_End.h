#pragma once
#include"../../Engine/GameObject/GameObject.h"

enum  ENDSTATE { WIN, LOSE };
class Scene_End :public GameObject
{
private:
	

	ENDSTATE endState_;
public:
	//�R���X�g���N�^
	Scene_End(GameObject* parent_/*, ENDSTATE state_*/);

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;

};

