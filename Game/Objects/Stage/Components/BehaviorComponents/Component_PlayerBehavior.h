#pragma once
#include "../Component.h"
#include <DirectXMath.h>
#include "../../StageObject.h"
#include <vector>
#include "../../../../../Engine/ResourceManager/Model.h"

enum PlayerState {
	PSTATE_IDLE = 0,
	PSTATE_WALK,
	PSTATE_WALKANDSHOOT,
	PSTATE_WALKANDMELEE,
	PSTATE_MELEE,
	PSTATE_SHOOT,
	PSTATE_DIE,
	PSTATE_DASH,
	PSTATE_MAX
	};
class CountDown;
class Component_PlayerBehavior : public Component
{
private:
	DirectX::XMVECTOR frontVec_;
	string targetName_;
	std::vector<RayCastData> rayHitObjectList_;
	float shootHeight_;
	bool isAnimationNow_;

	PlayerState nowState, prevState;
	bool isGameStart_;
public:
	Component_PlayerBehavior(string _name,StageObject* _holder,Component* _parent);

	void Initialize() override;
	void Update() override;
	void Release() override;
	
	void Save(json& _saveObj) override;
	void Load(json& _loadObj) override;
	void DrawData() override;
	
	void Idle();
	void Walk();
	void Shoot();
	void Dash();

	void SetState(PlayerState _state) { prevState = nowState; nowState = _state; }
	
	PlayerState GetState() const { return nowState; }

	bool IsDead();

	XMVECTOR CalcShootDirection();
};

