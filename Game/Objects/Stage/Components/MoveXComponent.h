#pragma once
#include "Component.h"

class MoveXComponent : public Component
{
	float moveSpeedX_;
public:
	MoveXComponent(StageObject* _holeder);
	void Initialize() override;
	void Update() override;
	void Release() override;

	void Save(json& _saveObj) override;
	void Load(json& _loadObj) override;
	void DrawData() override;
};

