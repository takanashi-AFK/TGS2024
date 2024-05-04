#pragma once
#include "Component.h"

class RotationComponent : public Component
{
public:
	RotationComponent(StageObject* _holeder);
	void Initialize() override;
	void Update() override;
	void Release() override;

	void Save(json& _saveObj) override;
	void Load(json& _loadObj) override;
	void DrawData() override;
};

