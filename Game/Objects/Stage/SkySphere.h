#pragma once
#include "StageObject.h"

// スカイスフィアを管理するクラス
class SkySphere : public StageObject
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="_parent">親オブジェクト</param>
	SkySphere(GameObject* _parent);

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize() override;

	/// <summary>
	/// 描画
	/// </summary>
	void Draw() override;
};

