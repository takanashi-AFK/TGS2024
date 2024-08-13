#pragma once
#include"../../Engine/GameObject/GameObject.h"
class Scene_Title :public GameObject
{

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="parent"></param>
	Scene_Title(GameObject* parent);

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

