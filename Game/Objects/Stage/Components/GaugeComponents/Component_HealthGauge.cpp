#include "Component_HealthGauge.h"

// インクルード
#include "../../../../../Engine/ImGui/imgui.h"


Component_HealthGauge::Component_HealthGauge(string _name, StageObject* _holder, Component* _parent)
	:Component_Gauge(_holder, _name, HealthGauge,_parent)
{

}

void Component_HealthGauge::Initialize()
{
}

void Component_HealthGauge::Update()
{
}

void Component_HealthGauge::Release()
{
}

void Component_HealthGauge::TakeDamage(float _damageValue)
{
	now_ -= _damageValue;
	//HPが0以下にならないようにする
	if (now_ < 0)now_ = 0;
}

void Component_HealthGauge::Heal(float _healValue)
{
	//HPが最大値を超えないようにする
	if (now_ + _healValue <= max_)now_ += _healValue;
}