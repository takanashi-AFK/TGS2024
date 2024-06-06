#pragma once

// インクルード
#include "../../Engine/GameObject/GameObject.h"


//テスト中
//前方宣言
class UIButton;
class UIPanel;


/// <summary>
/// テストシーンを管理するクラス
/// </summary>
class Scene_Test : public GameObject
{

private:

	//テスト中
	//ボタンクラスのインスタンス
	UIButton* button;

	//UIパネルクラスのインスタンス
	UIPanel* panel;

	//Scene_Testクラスのインスタンス
	Scene_Test * scene_test_;

public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="parent">親オブジェクト</param>
	Scene_Test(GameObject* parent);

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize() override;

	/// <summary>
	/// 更新
	/// </summary>
	void Update() override;

	/// <summary>
	/// 描画
	/// </summary>
	void Draw() override;

	/// <summary>
	/// 開放
	/// </summary>
	void Release() override;
};