#pragma once
#include"../../Engine/GameObject/GameObject.h"

class UIButton;
class UIPanel;


class Scene_End :public GameObject
{
private:
	//ボタンクラスのインスタンス
	UIButton* button;
	//UIパネルクラスのインスタンス
	UIPanel* panel;

public:
	//コンストラクタ
	Scene_End(GameObject* parent_);

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;

};

