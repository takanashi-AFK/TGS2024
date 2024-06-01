#pragma once
#include "../Component.h"

class Component_CactanBehavior : public Component
{
public:
	Component_CactanBehavior(string _name, StageObject* _holder, Component* _parent);
	void Initialize() override;
	void Update() override;
	void Release() override;

	void Save(json& _saveObj) override;
	void Load(json& _loadObj) override;

	void DrawData() override;
};

