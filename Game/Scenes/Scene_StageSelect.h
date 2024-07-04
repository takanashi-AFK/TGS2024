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
	float moveselectButton;//ボタンを動かすための速度
	//std::string easingfunc_;
	float maxButtonmove_;//開始位置が違くても指定した距離動くようにするのでそのための変数
public:
	Scene_StageSelect(GameObject* parent);

	void Initialize() override;

	void Update() override;

	void Draw() override;

	void Release() override;
};

