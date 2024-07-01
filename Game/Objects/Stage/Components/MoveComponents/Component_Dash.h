#pragma once
#include "../Component.h"
#include <DirectXMath.h>
using namespace DirectX;
class Component_Dash : public Component
{
private:

	XMVECTOR frontVec_;
	float moveDistance_;
	float totalMovedDistance_;
	float moveSpeed_;
	bool isActive_;
public:
	Component_Dash(string _name, StageObject* _holder, Component* _parent);
	void Initialize() override;
	void Update() override;
	void Release() override;
	void Save(json& _saveObj) override;
	void Load(json& _loadObj) override;
	void DrawData() override;

	void Execute() { isActive_ = true; }
};

