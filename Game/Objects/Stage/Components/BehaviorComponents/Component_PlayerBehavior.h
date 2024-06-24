#pragma once
#include "../Component.h"
#include <DirectXMath.h>

class Component_PlayerBehavior : public Component
{
private:
	DirectX::XMVECTOR frontVec_;
public:
	Component_PlayerBehavior(string _name,StageObject* _holder,Component* _parent);

	void Initialize() override;
	void Update() override;
	void Release() override;
	void DrawData() override;
	
	void OnCollision(GameObject* _target) override;	
};

