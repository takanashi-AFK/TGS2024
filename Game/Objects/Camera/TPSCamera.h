#pragma once
#include "../../../Engine/GameObject/GameObject.h"

class TPSCamera : public GameObject
{
private:
	XMFLOAT2 angle_;
	float sensitivity_;
	GameObject* pTarget_;
	bool isActive_;
public:
	TPSCamera(GameObject* parent);
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;

	void SetActive(bool isActive) { isActive_ = isActive; }
	void SetTarget(GameObject* target) { pTarget_ = target; }
	XMFLOAT2 GetAngle() { return angle_; }
};

