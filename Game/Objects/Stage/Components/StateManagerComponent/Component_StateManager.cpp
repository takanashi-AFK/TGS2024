#include "Component_StateManager.h"

// インクルードディレクティブ
#include "States/State.h"
#include "../../../Engine/ImGui/imgui.h"
#include "../../../../../Engine/DirectX/Input.h"
#include "StateObserver.h"

Component_StateManager::Component_StateManager(string _name, StageObject* _holder, Component* _parent)
	: Component(_holder, _name, ComponentType::StateManager, _parent)
{
}

void Component_StateManager::Initialize()
{
}

void Component_StateManager::Update()
{
	// 現在のステートが存在しない場合は処理を行わない
	if (currentState_ == nullptr)return;

	// 現在のステートを更新
	currentState_->Update();

	// ステート変更通知
	for (auto observer : observers_) {
		observer->OnStateChange(this);
	}
}

void Component_StateManager::Release()
{
}

void Component_StateManager::Save(json& _saveObj)
{
	// 現在のステート名を保存
	_saveObj["currentStateName"] = currentState_ != nullptr ? currentState_->GetName() : "null";

	// ステートリストを保存
	for (auto state : states_) {
		json stateObj;
		state.second->ChildSave(stateObj);
		_saveObj["states"][state.first] = stateObj;
	}
}

void Component_StateManager::Load(json& _loadObj)
{

	// ステートリストを読込
	for (auto state : _loadObj["states"].items()) {

		// ステートを生成
		State* s = CreateState(state.key(), (StateType)state.value()["type"].get<int>(),holder_);

		if(s != nullptr){
			s->ChildLoad(state.value());
			states_[state.key()] = s;
		}
	}

	// 現在のステート名を読込
	string currentStateName = _loadObj["currentStateName"].get<string>();
	currentState_ = states_[currentStateName];

	// 現在のステートが存在しない場合はステートリストの先頭を現在のステートに設定
	if (currentState_ == nullptr || !states_.empty() ) currentState_ = states_.begin()->second;
}

void Component_StateManager::DrawData()
{
	// 現在のステート名を表示
	ImGui::Text("currentState_: %s",currentState_ != nullptr ? currentState_->GetName().c_str() : "null");

	// ステートリストを表示
	if(ImGui::TreeNode("states_")) {

		// ステート追加ボタンを表示
		ImGui::SameLine();
		if(ImGui::SmallButton("Add State")) isAddStateWindowOpen_ = true;
		
		for (auto state : states_) {
			if(ImGui::TreeNode(state.first.c_str())){
				state.second->ChildDrawData();
				ImGui::TreePop();
			}

		}
		ImGui::TreePop();
	}

	// ステート追加ウィンドウを表示
	if (isAddStateWindowOpen_)DrawAddStateWindow();
}

void Component_StateManager::AddObserver(StateObserver* _observer)
{
	observers_.push_back(_observer);
}

void Component_StateManager::SetCurrentState(State* _state)
{
	if(_state == nullptr)return;
	currentState_ = _state;
}

void Component_StateManager::DrawAddStateWindow()
{
	ImGui::Begin("Add State..."); {

		// ステート名入力
		static char stateName[256];
		ImGui::InputText("State Name", stateName, 256);

		// ステートタイプを選択
		// タイプを選択
		static StateType stateType = StateType::None;	// 初期選択項目
		static std::string type = "NONE";		// 初期選択項目

		if (ImGui::BeginCombo(":seting type", type.c_str())) {
			for (int i = 0; i < StateType::None; i++) {
				std::string uiTypeString = StateTypeToString((StateType)i);
				if (uiTypeString.empty()) continue; // 空文字列を無視

				bool isSelected = (type == StateTypeToString((StateType)i));
				if (ImGui::Selectable(StateTypeToString((StateType)i).c_str(), isSelected)) {
					type = StateTypeToString((StateType)i);
					stateType = (StateType)i;
				}
				if (isSelected) {
					ImGui::SetItemDefaultFocus();
				}
			}
			ImGui::EndCombo();
		}

		if (ImGui::Button("add") || Input::IsKeyDown(DIK_RETURN)) {
			
			// ステートを追加
			states_[stateName] = CreateState(stateName, stateType,holder_);

			// 現在のステートが存在しない場合は追加したステートを現在のステートに設定
			if (currentState_ == nullptr) currentState_ = states_[stateName];
			
			// ウィンドウを閉じる
			isAddStateWindowOpen_ = false;
		}
	}
	ImGui::End();
}
