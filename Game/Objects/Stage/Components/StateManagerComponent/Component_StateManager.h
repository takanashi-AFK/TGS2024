#pragma once

// �C���N���[�h
#include "../Component.h"
#include "unordered_map"

// using�f�B���N�e�B�u
using std::unordered_map;

// �O���錾
class State;
class StateObserver;

class Component_StateManager : public Component
{
private:
	State* currentState_;	// ���݂̃X�e�[�g
	unordered_map<string,State*> states_;	// �X�e�[�g���X�g

	vector<StateObserver*> observers_;	// �X�e�[�g�I�u�U�[�o�[
public:
	// �R���X�g���N�^
	Component_StateManager(string _name, StageObject* _holder, Component* _parent);

	// ������
	void Initialize() override;
	
	// �X�V
	void Update() override;
	
	// �X�V
	void Release() override;

	// �ۑ�
	void Save(json& _saveObj) override;

	// �Ǎ�
	void Load(json& _loadObj) override;

	// ImGui�p�l���\��
	void DrawData() override;

	// observer�̒ǉ�
	void AddObserver(StateObserver* _observer);

	void SetCurrentState(State* _state);
	State* GetCurrentState() const { return currentState_; }

	unordered_map<string, State*> GetStates() const { return states_; }
private:
	bool isAddStateWindowOpen_;	// �X�e�[�g�ǉ��E�B���h�E�\���t���O
	void DrawAddStateWindow();
};

