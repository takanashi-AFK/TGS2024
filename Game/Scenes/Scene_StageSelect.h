#pragma once
#include "../../Engine/GameObject/GameObject.h"

class UIPanel;

class Scene_StageSelect: public GameObject
{

private:
	UIPanel* pUIPanel_;
	int selectIndex_;
public:
	Scene_StageSelect(GameObject* parent);

	void Initialize() override;

	void Update() override;

	void Draw() override;

	void Release() override;

private:
};

