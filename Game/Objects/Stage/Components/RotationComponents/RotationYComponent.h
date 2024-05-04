#pragma once
#include "../Component.h"

class RotationYComponent : public Component
{
	float rotateSpeed_;
	float angleY_;
public:
	RotationYComponent(StageObject* _holeder);
	void Initialize() override;
	void Update() override;
	void Release() override;

	void Save(json& _saveObj) override;
	void Load(json& _loadObj) override;
	void DrawData() override;
};

