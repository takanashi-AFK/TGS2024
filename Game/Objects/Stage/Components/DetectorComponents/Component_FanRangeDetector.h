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
	Component_FanRangeDetector(StageObject* _holder);

	void Initialize() override;
	void Update() override;
	void Release() override;

	void Save(json& _saveObj) override;
	void Load(json& _loadObj) override;
	void DrawData() override;

	// 範囲内に入っているかどうかを判定
	bool IsContains();
};

