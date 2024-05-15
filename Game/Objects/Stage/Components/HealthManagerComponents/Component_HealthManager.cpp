#include "Component_HealthManager.h"
#include "../../../../../Engine/ImGui/imgui.h"

Component_HealthManager::Component_HealthManager(StageObject* _holder)
	:Component(_holder, "Component_HealthManager", HealthManager),max_(0),hp_(0) {

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
}

void Component_HealthManager::Load(json& _loadObj)
{
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

	if (hp_ < 0)
		hp_ = 0;
}

void Component_HealthManager::Heal(float _healValue)
{
	if (hp_ + _healValue <= max_)
		hp_ += _healValue;
	return;
}

void Component_HealthManager::Reset()
{
	hp_ = max_;
}
