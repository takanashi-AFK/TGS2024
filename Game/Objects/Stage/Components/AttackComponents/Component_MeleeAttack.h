#pragma once
#include "Component_Attack.h"
#include "../../../../../Engine/Collider/BoxCollider.h"

class Component_MeleeAttack : public Component_Attack
{
private:
	XMVECTOR forward_; //前方向
	XMVECTOR prevFrontVec_;

public:
	Component_MeleeAttack(string _name, StageObject* _holder, Component* _parent);
	void Initialize() override;
	void Update() override;
	void Release() override;
	void DrawData() override;

	bool AutoDelete(float _time);

	void OnCollision(GameObject* _target) override;
	
	// 正面方向の設定
	void SetForward(XMVECTOR _forward) { forward_ = _forward; }
};

