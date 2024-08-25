#pragma once 
#include <string>
#include <unordered_map>
// ��ԕύX�����m����C���^�[�t�F�[�X�N���X
class StageObject;  
class State;
class Component_StateManager;
class StateObserver {
public:
	StateObserver() {};

    void Initialize(StageObject* holder_);

    // �C���^�[�t�F�[�X�������z�֐� 
    virtual void OnStateChange(std::unordered_map<std::string, State*>_states, State& _nowState) = 0;
};