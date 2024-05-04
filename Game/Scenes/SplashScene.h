#pragma once

// インクルード
#include "../../Engine/GameObject/GameObject.h"

// スプラッシュシーンを管理するクラス
class SplashScene : public GameObject
{
private:
	int imageHandle_;	// 画像番号
	float count_;
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="_parent">親オブジェクト</param>
	SplashScene(GameObject* _parent);

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

