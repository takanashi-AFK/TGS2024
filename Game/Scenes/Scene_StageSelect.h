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
	bool isSelectButtonMoving_;
	float moveselectButton;//�{�^���𓮂������߂̑��x
	//std::string easingfunc_;
	float maxButtonmove_;//�J�n�ʒu���Ⴍ�Ă��w�肵�����������悤�ɂ���̂ł��̂��߂̕ϐ�
public:
	Scene_StageSelect(GameObject* parent);

	void Initialize() override;

	void Update() override;

	void Draw() override;

	void Release() override;
};

