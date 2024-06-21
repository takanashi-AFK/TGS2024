#pragma once
#include "Component_Attack.h"
class Component_ShockWave : public Component_Attack
{
private:
	float shockwaveRange_;
	float shockwaveDamage_;
	StageObject* target_;
	string targetName_;
public:
	Component_ShockWave(string _name, StageObject* _holder, Component* _parent);
	void Initialize() override;
	void Update() override;
	void Release() override;
	void DrawData() override;
	void OnCollision(GameObject* _target) override;
	void Save(json& _saveObj) override;
	void Load(json& _loadObj) override;
};

