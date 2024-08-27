#pragma once
#include "State.h"

class State_Walk : public State
{
public:
	// コンストラクタ
	State_Walk(string _name, StageObject* _holder) :State(_name, StateType::Walk, _holder) {};

	// 初期化
	void Initialize() override;

	// 開始
	void Start() override;

	// 更新
	void Update() override;
};
