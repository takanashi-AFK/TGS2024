#pragma once
#include "../../Engine/GameObject/GameObject.h"

class  UIPanel;
class UIButton;
#include <vector>
class Scene_StageSelect: public GameObject
{

private:
	UIPanel* uipanel;//UIパネルのポインタ変数
	std::vector<UIButton*>stageImages;
	int StageIndex;
	bool isSelectButtonMoving_;//ボタンが動いてるかどうか
	float moveselectButton;//ボタンを動かすための割合
	std::string easingfunc_;//いーじんぐ
	float maxButtonmove_;//指定距離の変数

public:
	Scene_StageSelect(GameObject* parent);

	void Initialize() override;

	void Update() override;

	void Draw() override;

	void Release() override;
};

