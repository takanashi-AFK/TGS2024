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
	string easingfunc;//いーじんぐ関数の種類を入れる変数
	float proportionstageImages;//いつか使うであろうイージングの割合変数
public:
	Scene_StageSelect(GameObject* parent);

	void Initialize() override;

	void Update() override;

	void Draw() override;

	void Release() override;
};

