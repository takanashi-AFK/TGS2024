#pragma once
#include "Component_StateManager.h"
#include "../../../../../Engine/ImGui/imgui.h"
#include <unordered_map>
#include "../Component.h"
#include "../../../../../Engine/Global.h"
#include "State.h"

enum StateType {
    PLAYER_STATE_WALK = 0,
    STATE_MAX
    // ���̏�Ԃ̃^�C�v
};

// ��ԊǗ��R���|�[�l���g
class Component_StateManager : public Component
{
private:
    std::unordered_map<string, State*> stateList_; // �ێ������Ԃ̔z��
    string currentStateKey_;  // ���݂̏�Ԃ��w�肷��L�[

    float changeLimit_;       // ��Ԃ�ύX����ہA�ύX�܂Ŏ��Ԃ�v����ꍇ�̃��~�b�^�[
    float count_;             // �V�̃J�E���^
    string changeStateKey_;   // �V�̕ύX��̏�Ԃ��w�肷��L�[
    bool g_isAddStateWindowOpen;

    int animSpeed_;
    int animMaxFrame_;
    int animStartFrame_;
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

    State* CreateState(StateType type, const string& name);

    State* GetCurrentState(string _key);
};