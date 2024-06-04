#pragma once
#include "../Component.h"

class Component_PlayerBehavior : public Component
{
public:
	Component_PlayerBehavior(string _name,StageObject* _holder,Component* _parent);

	void Initialize() override;
	void Update() override;
	void Release() override;
	
	void OnCollision(GameObject* _target) override;	
};

