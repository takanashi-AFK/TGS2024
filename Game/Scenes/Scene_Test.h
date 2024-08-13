#pragma once
#include"../../Engine/GameObject/GameObject.h"
class Scene_Test :public GameObject
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="parent"></param>
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

