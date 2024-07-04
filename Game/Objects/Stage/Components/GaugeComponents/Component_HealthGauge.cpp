#include "Component_HealthGauge.h"

// インクルード
#include "../../../../../Engine/ImGui/imgui.h"

Component_HealthGauge::Component_HealthGauge(string _name, StageObject* _holder, Component* _parent)
	:Component_Gauge(_holder, _name, HealthGauge,_parent),maxHp_(0),nowHp_(0)
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

void Component_HealthGauge::Save(json& _saveObj)
{
	_saveObj["maxnowHp_"] = maxHp_;
	_saveObj["nowHp_"] = nowHp_;
}

void Component_HealthGauge::Load(json& _loadObj)
{
	if (_loadObj.contains("maxHp_"))maxHp_ = _loadObj["maxHp_"];
	if (_loadObj.contains("nowHp_"))nowHp_ = _loadObj["nowHp_"];
}

void Component_HealthGauge::DrawData()
{
	if (ImGui::Button("HP Heal"))
	{
		Heal(10.f);
	}
	if (ImGui::Button("Damage"))
	{
		TakeDamage(10.f);
	}


	static float tempHP = 0;
	ImGui::DragFloat("HP", &tempHP, 1.0f, 0.0f, 100.0f);
	if (ImGui::Button("DragSetHP"))
	{
		SetHP(tempHP);
	}

	static float tempMax = 0;
	ImGui::DragFloat("Max", &tempMax, 1.0f, 0.0f, 100.0f);
	if (ImGui::Button("DragSetMax"))
	{
		SetMax(tempMax);
	}

	if (ImGui::Button("Reset"))
	{
		Reset();
	}

	ImGui::Text("HP:%f", nowHp_);
	ImGui::Text("MaxHP:%f", maxHp_);

}

float Component_HealthGauge::GetHP() const
{
	return nowHp_;
}

void Component_HealthGauge::SetHP(float _newHP)
{
	if(_newHP <= maxHp_)nowHp_ = _newHP;
}

float Component_HealthGauge::GetMax() const
{
	return maxHp_;
}

void Component_HealthGauge::SetMax(float _newMax)
{
	maxHp_ = _newMax;
}

void Component_HealthGauge::TakeDamage(float _damageValue)
{
	nowHp_ -= _damageValue;
	//HPが0以下にならないようにする
	if (nowHp_ < 0)nowHp_ = 0;
}

void Component_HealthGauge::Heal(float _healValue)
{
	//HPが最大値を超えないようにする
	if (nowHp_ + _healValue <= maxHp_)nowHp_ += _healValue;
}

void Component_HealthGauge::Reset()
{
	nowHp_ = maxHp_;
}
