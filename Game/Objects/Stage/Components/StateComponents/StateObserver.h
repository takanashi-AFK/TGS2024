#pragma once

// �C���N���[�h

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

