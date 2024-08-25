#pragma once 
#include <string>
#include <unordered_map>
// 状態変更を検知するインターフェースクラス
class StageObject;  
class State;
class Component_StateManager;
class StateObserver {
public:
	StateObserver() {};

    void Initialize(StageObject* holder_);

    // インターフェース純粋仮想関数 
    virtual void OnStateChange(std::unordered_map<std::string, State*>_states, State& _nowState) = 0;
};