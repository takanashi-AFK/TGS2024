#pragma once

// �C���N���[�h
#include <unordered_map>
#include "States/State.h"

using std::unordered_map;
class Component_StateManager;

class StageObject;

class StateObserver
{
public:
	// ������
	// �N���X���p�������ꍇ�A�K���Ăяo������
	bool Entry(StageObject* holder_);

	// �X�e�[�g�ύX�ʒm
	virtual void OnStateChange(Component_StateManager* _stateManager) = 0;
};

