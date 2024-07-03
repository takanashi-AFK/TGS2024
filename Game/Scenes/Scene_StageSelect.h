#pragma once
#include "../../Engine/GameObject/GameObject.h"

class  UIPanel;
class UIButton;

class Scene_StageSelect: public GameObject
{
private:
	UIPanel* uipanel;
	vector<UIButton*>stageImages;
	int StageIndex;
public:
	Scene_StageSelect(GameObject* parent);

	void Initialize() override;

	void Update() override;

	void Draw() override;

	void Release() override;
};

