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
	bool isRightButtonMoving_;//ボタンが右方向に動いてるかどうか
	bool isLeftSelectButtonMoving_;//-方向に動いているかどうか
	float moveselectButton;//ボタンを動かすための割合
	std::string easingfunc_;//いーじんぐ

public:
	Scene_StageSelect(GameObject* parent);

	void Initialize() override;

	void Update() override;

	void Draw() override;

	void Release() override;

private:
	/// <summary>
	/// ボタンが右に動く関数
	/// </summary>
	void RightButtonMoving();

	/// <summary>
	/// ボタンが左に動く関数
	/// </summary>
	void LeftButtonMoving();

	void MoveButtons(bool _moving);
};

