#pragma once
#include "../Component.h"
#include <DirectXMath.h>
#include "../StateComponents/StateObserver.h"
class State;
using namespace DirectX;

class Component_WASDInputMove : public Component, StateObserver
{
private:
	bool isMove_;
	XMVECTOR dir_;
public:
	Component_WASDInputMove(string _name, StageObject* _holder, Component* _parent);
	void Initialize() override;
	void Update() override;
	void Release() override;
	void DrawData() override;
	void Save(json& _saveObj) override;
	void Load(json& _loadObj) override;
	void OnStateChange(std::unordered_map<string, State*>_states,State& _nowState) override;
	XMVECTOR GetMoveDirection() { return dir_; }
	bool GetIsMove() { return isMove_; }

private:
	void Move(XMVECTOR _dir, float _speed);
};

