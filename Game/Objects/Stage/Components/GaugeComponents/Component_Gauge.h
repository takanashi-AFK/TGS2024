#pragma once
//インクルード
#include"../Component.h"


/// <summary>
/// ゲージを管理するコンポーネント
/// </summary>
class Component_Gauge :public Component
{
protected:
	float max_;	// 最大値
	float now_;	// 現在値

public:
	Component_Gauge(StageObject* _holder, string _name, ComponentType _type, Component* _parent);

	void Save(json& _saveObj) override;
	void Load(json& _loadObj) override;
	void DrawData() override;

	float GetNow() const { return now_; }
	void SetNow(float _newNow) { now_ = _newNow; }
	float GetMax() const { return max_; }
	void SetMax(float _newMax) { max_ = _newMax; }

	void AdjustToMax() { now_ = max_; }
};
