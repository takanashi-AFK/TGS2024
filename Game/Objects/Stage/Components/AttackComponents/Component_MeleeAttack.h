#pragma once
#include "Component_Attack.h"
#include "../../../../../Engine/Collider/BoxCollider.h"
#include "../../../../../EffekseeLib/EffekseerVFX.h"

class Component_MeleeAttack : public Component_Attack
{
private:
	XMVECTOR forward_; //‘O•ûŒü

	std::shared_ptr<EFFEKSEERLIB::EFKTransform> mt;
public:
	Component_MeleeAttack(string _name, StageObject* _holder, Component* _parent);
	void Initialize() override;
	void Update() override;
	void Release() override;
	void DrawData() override;
	void AutoDelete(float _time);
	void OnCollision(GameObject* _target) override;
	
	// ³–Ê•ûŒü‚Ìİ’è
	void SetForward(XMVECTOR _forward) { forward_ = _forward; }
};

