#pragma once
#include "../Component.h"
#include <DirectXMath.h>
#include "../../StageObject.h"
#include <vector>
#include "../../../../../Engine/ResourceManager/Model.h"
class Component_PlayerBehavior : public Component
{
private:
	DirectX::XMVECTOR frontVec_;
	StageObject* target_;	// ターゲット
	string targetName_;
	std::vector<RayCastData> rayHitObjectList_;

public:
	Component_PlayerBehavior(string _name,StageObject* _holder,Component* _parent);

	void Initialize() override;
	void Update() override;
	void Release() override;
	void DrawData() override;
	
	void OnCollision(GameObject* _target) override;	

	//bool IsEnemyInRect(StageObject* _target);

	//XMFLOAT3 ConvertTo2DPos(StageObject* _target);
};

