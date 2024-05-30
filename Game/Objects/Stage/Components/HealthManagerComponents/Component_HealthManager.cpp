#include "Component_HealthManager.h"

// インクルード
#include "../../../../../Engine/ImGui/imgui.h"

Component_HealthManager::Component_HealthManager(string _name, StageObject* _holder)
	:Component(_holder, _name, HealthManager),max_(0),hp_(0) 
{

}

void Component_HealthManager::Initialize()
{
}

void Component_HealthManager::Update()
{
}

void Component_HealthManager::Release()
{
}

void Component_HealthManager::Save(json& _saveObj)
{
	_saveObj["max_"] = max_;
	_saveObj["hp_"] = hp_;
}

void Component_HealthManager::Load(json& _loadObj)
{
	if (_loadObj.contains("max_"))max_ = _loadObj["max_"];
	if (_loadObj.contains("hp_"))hp_ = _loadObj["hp_"];
}

void Component_HealthManager::DrawData()
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

	ImGui::Text("HP:%f", hp_);
	ImGui::Text("MaxHP:%f", max_);

}

float Component_HealthManager::GetHP() const
{
	return hp_;
}

void Component_HealthManager::SetHP(float _newHP)
{
	if(_newHP <= max_)
	hp_ = _newHP;
}

float Component_HealthManager::GetMax() const
{
	return max_;
}

void Component_HealthManager::SetMax(float _newMax)
{
	max_ = _newMax;
}

void Component_HealthManager::TakeDamage(float _damageValue)
{
	hp_ -= _damageValue;
	//HPが0以下にならないようにする
	if (hp_ < 0)
		hp_ = 0;
}

void Component_HealthManager::Heal(float _healValue)
{
	//HPが最大値を超えないようにする
	if (hp_ + _healValue <= max_)
		hp_ += _healValue;
	return;
}

void Component_HealthManager::Reset()
{
	hp_ = max_;
}
