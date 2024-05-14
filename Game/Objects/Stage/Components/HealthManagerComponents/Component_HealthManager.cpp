#include "Component_HealthManager.h"
#include "../../../../../Engine/ImGui/imgui.h"

Component_HealthManager::Component_HealthManager(StageObject* _holder)
	:Component(_holder, "Component_HealthManager", HealthManager),max_(0),hp_(0) {

}

float Component_HealthManager::GetHP() const
{
	return hp_;
}

void Component_HealthManager::SetHP(int _newHP)
{
	hp_ = _newHP;
}

void Component_HealthManager::TakeDamage(int _damageValue)
{
	hp_ -= _damageValue;

	if (hp_ < 0)
		hp_ = 0;
}

void Component_HealthManager::Heal(int _healValue)
{
	hp_ += _healValue;
}
