#pragma once
#include "../Component.h"
#include <DirectXMath.h>
#include "../../../EffekseeLib/EffekseerVFX.h"/*ššš*/
#include "../../../../../Engine/Global.h"

using namespace DirectX;

class Component_WASDInputMove : public Component
{
private:
	bool isMove_;
	XMVECTOR dir_;

	// effekseer: •ÏŒ`s—ñ
	std::shared_ptr<EFFEKSEERLIB::EFKTransform> mt;/*ššš*/
	EffectData data_;

public:
	Component_WASDInputMove(string _name, StageObject* _holder, Component* _parent);
	void Initialize() override;
	void Update() override;
	void Release() override;
	void DrawData() override;
	void Save(json& _saveObj) override;
	void Load(json& _loadObj) override;
	XMVECTOR GetMoveDirection() const { return dir_; }
	bool IsMove() const { return isMove_; }

private:
	void Move(XMVECTOR _dir, float _speed);
};

