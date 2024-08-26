#include "Component_StateManager.h"
#include "../../StageObject.h"
#include "PlayerState/PlayerState_Walk.h"
#include "../StateComponents/StateObserver.h"
#include "../../../../../Engine/DirectX/Input.h"

#include "PlayerState/State_Idle.h"

Component_StateManager::Component_StateManager(string _name, StageObject* _holder, Component* _parent)
	: Component(_holder, _name, StateManager,_parent)
{
}

void Component_StateManager::Initialize()
{
	// 各状態の初期化を行う
	for (auto state : stateList_) {
		state.second->ChildInitialize();
	}
}

void Component_StateManager::Update()
{
	// 状態の変更処理 //////
	if(currentStateKey_ != "") {
		// 状態が遷移可能な場合遷移する
		if (count_ >= changeLimit_) {
			currentStateKey_ = changeStateKey_;  // 変更
			stateList_[currentStateKey_]->Start();
		}
		count_ += 1 / FPS;  // カウントを進める
	// キーで指定された状態が存在するかどうかを確認し、現在の状態の更新処理を実行
	if (stateList_.find(currentStateKey_) != stateList_.end()) stateList_[currentStateKey_]->Update();
	}

	// 現在どの状態なのかを判定し、currentStateに代入
	for (auto* observer : observers_) {
		observer->OnStateChange(this);
	}

}

void Component_StateManager::Release()
{
}

void Component_StateManager::DrawData()
{
	// 状態を追加
	if (ImGui::SmallButton("Add State"))isAddStateWindowOpen_ = true;
	// 状態追加用ウィンドウ
	if (isAddStateWindowOpen_)DrawAddStateWindow(this);

	// 追加されている状態をツリーノードで表示
	if (ImGui::TreeNode("State list")) {
		// ここに現在追加されているStateを表示
		for (auto state : stateList_) { 
			if (ImGui::TreeNode("state")) {

				const type_info& id = typeid(*state.second);
				ImGui::Text("Name : %s", state.second->GetName().c_str());
				ImGui::Text("Class : %s", id.name());
				if (holder_->GetModelFilePath() != "") {
				ImGui::Text("Base Model : %s", holder_->GetModelFilePath().c_str());
				}
				std::vector<ModelData> modelDataList = state.second->GetModelDatas();

				for (auto modelData : modelDataList) {
					ImGui::Text("Model : %s", modelData.filePath.c_str());
				}

				if (ImGui::SmallButton("Add Model"))state.second->AddModel();
				state.second->DrawAddModelWindow();
				ImGui::TreePop();
			}
		}
		ImGui::TreePop();
	}
}

void Component_StateManager::DrawAddStateWindow(Component_StateManager* _stateManager) 
{

	ImGui::Begin("Add State..."); {

		// ステート名入力
		static char stateName[256];
		ImGui::InputText("State Name", stateName, 256);

		// ステートタイプを選択
		// タイプを選択
		static STATE_TYPE stateType = STATE_TYPE::None;	// 初期選択項目
		static std::string type = "NONE";		// 初期選択項目

		if (ImGui::BeginCombo(":seting type", type.c_str())) {
			for (int i = 0; i < STATE_TYPE::None; i++) {
				std::string uiTypeString = StateTypeToString((STATE_TYPE)i);
				if (uiTypeString.empty()) continue; // 空文字列を無視

				bool isSelected = (type == StateTypeToString((STATE_TYPE)i));
				if (ImGui::Selectable(StateTypeToString((STATE_TYPE)i).c_str(), isSelected)) {
					type = StateTypeToString((STATE_TYPE)i);
					stateType = (STATE_TYPE)i;
				}
				if (isSelected) {
					ImGui::SetItemDefaultFocus();
				}
			}
			ImGui::EndCombo();
		}

		if (ImGui::Button("add") || Input::IsKeyDown(DIK_RETURN)) {

			// ステートを追加
			stateList_[stateName] = CreateState(stateName, stateType);

			// 現在のステートが存在しない場合は追加したステートを現在のステートに設定
			if (currentState_ == nullptr) currentState_ = stateList_[stateName];

			// ウィンドウを閉じる
			isAddStateWindowOpen_ = false;
		}
	}
	ImGui::End();
}

void Component_StateManager::Save(json& _saveObj)
{
	// 各状態の保存
	for (auto state : stateList_) {
		state.second->Save(_saveObj);
	}
	_saveObj["currentStateKey_"] = currentStateKey_;
}

void Component_StateManager::Load(json& _loadObj)
{
	// 各状態の読み込み
	for (auto state : stateList_) {
		state.second->Load(_loadObj);
	}
	if (_loadObj.contains("currentStateKey_"))currentStateKey_=_loadObj["currentStateKey_"];
}

State* Component_StateManager::CreateState(string _name, STATE_TYPE _type)
{
	switch (_type)
	{
	case Idle: return new State_Idle(_name);
	default: return nullptr;
	}
	// ここにelseでほかの状態を追加
}

State* Component_StateManager::GetCurrentState()
{
	return stateList_[currentStateKey_];
}
