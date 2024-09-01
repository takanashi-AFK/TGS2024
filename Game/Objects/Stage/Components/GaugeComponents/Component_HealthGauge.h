#pragma once
//インクルード
#include"Component_Gauge.h"

/// <summary>
/// 体力の増減を管理するコンポーネント
/// </summary>
class Component_HealthGauge :public Component_Gauge
{
public:
	Component_HealthGauge(string _name, StageObject* _holder, Component* _parent);

	void Initialize() override;
	void Update() override;
	void Release() override;

	void TakeDamage(float _damageValue);
	void Heal(float _healValue);
	bool IsDead() const { return now_ <= 0; }
};