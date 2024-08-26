#pragma once
#include "../../../../../Engine/ResourceManager/Model.h"
#include "../../StageObject.h"
#include "../Component.h"
#include <DirectXMath.h>
#include <vector>

class Component_PlayerBehavior : public Component
{
private:
	DirectX::XMVECTOR frontVec_;
	StageObject* target_;	
	string targetName_;
	std::vector<RayCastData> rayHitObjectList_;
	float shootHeight_;
	bool isAnimationNow_;

public:
	Component_PlayerBehavior(string _name,StageObject* _holder,Component* _parent);

	void Initialize() override;
	void Update() override;
	void Release() override;
	void DrawData() override;
	
	void OnCollision(GameObject* _target, Collider* _collider) override;

	void Idle();
	void Walk();
	void WalkAndShoot();
	void WalkAndMelee();
	void Melee();
	void Shoot();
	
	void ShootExe();

	bool IsDead();

	//bool IsEnemyInRect(StageObject* _target);

	//XMFLOAT3 ConvertTo2DPos(StageObject* _target);
};

