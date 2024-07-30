#pragma once
#include "../Component.h"
#include <DirectXMath.h>
using namespace DirectX;

class Component_WASDInputMove : public Component
{
private:
	bool isActive_;
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
	void Execute(){isActive_ = true;}
	void Stop(){isActive_ = false;}
	XMVECTOR GetMoveDirction() { return dir_; }
	bool GetIsMove() { return isMove_; }

private:
	void Move(XMVECTOR _dir, float _speed);
};

