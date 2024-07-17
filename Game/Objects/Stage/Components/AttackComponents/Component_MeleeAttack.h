#pragma once
#include "Component_Attack.h"
#include "../../../../../Engine/Collider/BoxCollider.h"

class Component_MeleeAttack : public Component_Attack
{
private:
	XMVECTOR forward_; 
	XMVECTOR prevFrontVec_;
	bool isHit_;

public:
	Component_MeleeAttack(string _name, StageObject* _holder, Component* _parent);
	void Initialize() override;
	void Update() override;
	void Release();
	void DrawData() override;

	bool AutoDelete(float _time);

	void OnCollision(GameObject* _target, Collider* _collider) override;

	void SetForward(XMVECTOR _forward) { forward_ = _forward; }
};