#pragma once
#include "../../Engine/GameObject/GameObject.h"

class  UIPanel;
class UIButton;
#include <vector>
class Scene_StageSelect: public GameObject
{
private:
	UIPanel* uipanel;
	std::vector<UIButton*>stageImages;
	int StageIndex;
	string easingfunc;//���[���񂮊֐��̎�ނ�����ϐ�
	float proportionstageImages;//�����g���ł��낤�C�[�W���O�̊����ϐ�
public:
	Scene_StageSelect(GameObject* parent);

	void Initialize() override;

	void Update() override;

	void Draw() override;

	void Release() override;
};

