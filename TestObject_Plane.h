#pragma once
#include "Engine/GameObject/GameObject.h"

class TestObject_Plane : public GameObject
{
	int modelHandle_;
public:
	TestObject_Plane(GameObject* _parent);
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;
};
