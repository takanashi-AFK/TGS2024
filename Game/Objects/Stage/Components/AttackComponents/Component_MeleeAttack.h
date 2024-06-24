#pragma once
#include "Component_Attack.h"
#include "../../../../../Engine/Collider/BoxCollider.h"

class Component_MeleeAttack : public Component_Attack
{
private:
	BoxCollider* collider_;
	XMFLOAT3 colliderPos_;
public:
	Component_MeleeAttack(string _name, StageObject* _holder, Component* _parent);
	void Initialize() override;
	void Update() override;
	void Release() override;
	void DrawData() override;

	void AutoDelete(float _time);
	void SetColliderPosition(XMFLOAT3 _pos) { colliderPos_ = _pos; }
};

