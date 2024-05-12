#pragma once
#include "../Component.h"

class Component_CircleRangeDetector : public Component
{
private:
	
	StageObject* target_;  // 対象オブジェクト
	float radius_;  // 半径
	bool isContains_;    // 当たり判定フラグ

public:
	Component_CircleRangeDetector(StageObject* _holder);

	void Initialize() override;
	void Update() override;
	void Release() override;

	void Save(json& _saveObj) override;
	void Load(json& _loadObj) override;
	void DrawData() override;
// setter
	void SetRadius(float _radius) { radius_ = _radius; }
	void SetTarget(StageObject* _target) { target_ = _target; }

// getter
	float GetRadius() { return radius_; }
	bool IsContains() { return isContains_; }
	StageObject* GetTarget() { return target_; }

private:
	// 範囲内に入っているかどうかを判定
	bool Contains();

};

