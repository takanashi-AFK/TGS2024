#pragma once

// インクルード
#include "../../Engine/GameObject/GameObject.h"

//前方宣言
class UIButton;
class UIPanel;

/// <summary>
/// テストシーンを管理するクラス
/// </summary>
class Scene_Test : public GameObject
{
private:
	//ボタンクラスのインスタンス
	UIButton* button;
	//UIパネルクラスのインスタンス
	UIPanel* panel;

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