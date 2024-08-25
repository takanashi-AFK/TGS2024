#pragma once

// インクルード
#include "../Component.h"
#include "unordered_map"

// usingディレクティブ
using std::unordered_map;

// 前方宣言
class State;
class StateObserver;

class Component_StateManager : public Component
{
private:
	State* currentState_;	// 現在のステート
	unordered_map<string,State*> states_;	// ステートリスト

	vector<StateObserver*> observers_;	// ステートオブザーバー
public:
	// コンストラクタ
	Component_StateManager(string _name, StageObject* _holder, Component* _parent);

	// 初期化
	void Initialize() override;
	
	// 更新
	void Update() override;
	
	// 更新
	void Release() override;

	// 保存
	void Save(json& _saveObj) override;

	// 読込
	void Load(json& _loadObj) override;

	// ImGuiパネル表示
	void DrawData() override;

	// observerの追加
	void AddObserver(StateObserver* _observer);

	void SetCurrentState(State* _state);
	State* GetCurrentState() const { return currentState_; }

	unordered_map<string, State*> GetStates() const { return states_; }
private:
	bool isAddStateWindowOpen_;	// ステート追加ウィンドウ表示フラグ
	void DrawAddStateWindow();
};

