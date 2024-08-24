#pragma once
#include"StageObject.h"
class SkySphere :public StageObject
{
public:
	SkySphere(GameObject* parent_);

	void Initialize() override;

	void Update() override;

};

