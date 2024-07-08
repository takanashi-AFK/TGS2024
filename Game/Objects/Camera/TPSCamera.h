#pragma once
#include "../../../Engine/GameObject/GameObject.h"
#include "../../../Engine/Json/JsonReader.h"

class TPSCamera : public GameObject
{
private:
	XMFLOAT2 angle_;
	float sensitivity_;
	GameObject* pTarget_;
	string targetName_;
	bool isActive_;
	float targetHeight_;
	float targetDistance_;
	XMVECTOR prevAxis_;
public:
	TPSCamera(GameObject* parent);
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;

	void DrawData();
	void Save(json& saveObj);
	void Load(json& loadObj);

	void SetActive(bool isActive) { isActive_ = isActive; }
	void SetTarget(GameObject* target) { pTarget_ = target; }
	XMFLOAT2 GetAngle() { return angle_; }
};

