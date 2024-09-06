#pragma once
#include "../Component.h"
#include "../../Components/BehaviorComponents/Component_PlayerBehavior.h"
#include <map>
class Component_Motion : public Component
{
protected:
	std::map<PlayerState, int>motionModelMap_;

public:
	Component_Motion(string _name, StageObject* _holder,ComponentType _type, Component* _parent);
	void Initialize() override;
	void Update() override;
	void Release() override;
	void DrawData() override;

	void PlayMotion(int _start,int _end, int _speed);
};

