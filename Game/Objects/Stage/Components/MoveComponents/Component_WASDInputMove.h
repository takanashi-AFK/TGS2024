#pragma once
#include "../Component.h"
#include <DirectXMath.h>
using namespace DirectX;

class Component_WASDInputMove : public Component
{
public:
	Component_WASDInputMove(string _name, StageObject* _holder, Component* _parent);
	void Initialize() override;
	void Update() override;
	void Release() override;
	void DrawData() override;
	
	void Execute(){isActive_ = true;}
	void Stop(){isActive_ = false;}

private:
	void Move(XMVECTOR _dir, float _speed);
};

