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
    // 他の状態のタイプ
};

// 状態管理コンポーネント
class Component_StateManager : public Component
{
private:
    std::unordered_map<string, State*> stateList_; // 保持する状態の配列
    string currentStateKey_;  // 現在の状態を指定するキー

    float changeLimit_;       // 状態を変更する際、変更まで時間を要する場合のリミッター
    float count_;             // 〃のカウンタ
    string changeStateKey_;   // 〃の変更後の状態を指定するキー
    bool g_isAddStateWindowOpen;

    int animSpeed_;
    int animMaxFrame_;
    int animStartFrame_;
public:

    Component_StateManager(string _name, StageObject* _holder, Component* _parent);
    // 初期化処理
    void Initialize() override;

    // 更新処理
    void Update()override;

	void Release()override;

    // debug時、ImGuiで情報を表示する関数
    void DrawData()override;

	void DrawAddStateWindow(Component_StateManager* _stateManager);

    // 状態を変更する為の関数
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