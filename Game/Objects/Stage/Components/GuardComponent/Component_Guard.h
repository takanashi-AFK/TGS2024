#pragma once
#include "../../Components/Component.h"
#include <list>

class BoxCollider;

class Component_Guard : public Component
{
private:

	BoxCollider* guardCollider_;
public:
	Component_Guard(string _name, StageObject* _holder, Component* _parent);
	void Initialize() override;
	void Update() override;
	void Release() override;
	void DrawData() override;

	void Save(json& _saveObj) override;
	void Load(json& _loadObj) override;
};

