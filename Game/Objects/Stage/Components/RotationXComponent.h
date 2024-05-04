#pragma once
#include "Component.h"

class RotationXComponent : public Component
{
	float rotateSpeed_;
	float angleX_;
public:
	RotationXComponent(StageObject* _holeder);
	void Initialize() override;
	void Update() override;
	void Release() override;

	void Save(json& _saveObj) override;
	void Load(json& _loadObj) override;
	void DrawData() override;
};

