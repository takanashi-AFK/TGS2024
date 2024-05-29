#pragma once

#include "../Component.h"
#include <DirectXMath.h>

using namespace DirectX;

class Component_FanRangeDetector : public Component
{
private:
	StageObject* target_;	// 対象オブジェクト
	float length_;			// 長さ
	float angle_;			// 角度
	XMVECTOR direction_;	// 方向
	bool isContains_;		// 当たり判定フラグ

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="_holder">保有者</param>
	Component_FanRangeDetector(StageObject* _holder);

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize() override;

	/// <summary>
	/// 更新
	/// </summary>
	void Update() override;

	/// <summary>
	/// 解放
	/// </summary>
	void Release() override;

	/// <summary>
	/// 保存
	/// </summary>
	/// <param name="_saveObj">保存情報</param>
	void Save(json& _saveObj) override;

	/// <summary>
	/// 読込
	/// </summary>
	/// <param name="_loadObj">読込情報</param>
	void Load(json& _loadObj) override;

	/// <summary>
	/// ImGuiパネル表示
	/// </summary>
	void DrawData() override;

	// 範囲内に入っているかどうかを判定
	bool IsContains();
};

