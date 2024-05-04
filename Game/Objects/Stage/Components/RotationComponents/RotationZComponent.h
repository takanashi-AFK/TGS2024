#pragma once
#include "../Component.h"

class RotationZComponent : public Component
{
	float rotateSpeed_;
	float angleZ_;
public:
	RotationZComponent(StageObject* _holeder);
	void Initialize() override;
	void Update() override;
	void Release() override;

	void Save(json& _saveObj) override;
	void Load(json& _loadObj) override;
	void DrawData() override;
};

