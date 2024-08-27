#pragma once
#include "State.h"

class State_Walk : public State
{
public:
	// �R���X�g���N�^
	State_Walk(string _name, StageObject* _holder) :State(_name, StateType::Walk, _holder) {};

	// ������
	void Initialize() override;

	// �J�n
	void Start() override;

	// �X�V
	void Update() override;
};
