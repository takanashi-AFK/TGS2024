#pragma once
#include "../../Engine/GameObject/GameObject.h"

class  UIPanel;
class UIButton;
#include <vector>
class Scene_StageSelect: public GameObject
{

private:
	UIPanel* uipanel;//UI�p�l���̃|�C���^�ϐ�
	std::vector<UIButton*>stageImages;
	int StageIndex;
	bool isSelectButtonMoving_;//�{�^���������Ă邩�ǂ���
	float moveselectButton;//�{�^���𓮂������߂̊���
	std::string easingfunc_;//���[����
	float maxButtonmove_;//�w�苗���̕ϐ�

public:
	Scene_StageSelect(GameObject* parent);

	void Initialize() override;

	void Update() override;

	void Draw() override;

	void Release() override;
};

