#pragma once
#include "../../../../../Engine/Global.h"
#include "../../../../../Engine/ImGui/imgui.h"
#include "../Component.h"
#include "State.h"
#include <unordered_map>
class StateObserver;
using std::string;
// ��ԊǗ��R���|�[�l���g
class Component_StateManager : public Component
{
private:
    std::unordered_map<string, State*> stateList_; // �ێ������Ԃ̔z��
    string currentStateKey_;  // ���݂̏�Ԃ��w�肷��L�[
    std::vector<StateObserver*> observers_;
    State* currentState_;
    float changeLimit_;       // ��Ԃ�ύX����ہA�ύX�܂Ŏ��Ԃ�v����ꍇ�̃��~�b�^�[
    float count_;             // �V�̃J�E���^
    string changeStateKey_;   // �V�̕ύX��̏�Ԃ��w�肷��L�[
    bool isAddStateWindowOpen_;
public:

    Component_StateManager(string _name, StageObject* _holder, Component* _parent);
    // ����������
    void Initialize() override;

    // �X�V����
    void Update()override;

	void Release()override;

    // debug���AImGui�ŏ���\������֐�
    void DrawData()override;

	void DrawAddStateWindow(Component_StateManager* _stateManager);

    // ��Ԃ�ύX����ׂ̊֐�
    bool ChangeState(string _key) {ChangeState(_key, 0);}

    bool ChangeState(string _key, float _limit) {
        changeStateKey_ = _key;
        changeLimit_ = _limit;
        count_ = 0;
    }

    bool AddState(State* _state) {
        if (_state == nullptr) return false;
        stateList_[_state->GetName()] = _state;
        return true;
    }

	void Save(json& _saveObj)override;
	void Load(json& _loadObj)override;

    State* CreateState(string _name, STATE_TYPE _type);

    State* GetCurrentState();

    std::unordered_map<string, State*> GetStates() const { return stateList_; }

    void SetCurrentState(State* _state) { currentState_ = _state; }

	void AddObserver(StateObserver* observer) { observers_.push_back(observer); }
};