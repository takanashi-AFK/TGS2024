#pragma once
#include "../Component.h"

class Component_OtiBehavior : public Component
{
private:
	
public:
	Component_OtiBehavior(StageObject* _holder);
	
	void Initialize() override;
	void Update() override;
	void Release() override;

	void Save(json& _saveObj) override;
	void Load(json& _loadObj) override;
	void DrawData() override;
};

