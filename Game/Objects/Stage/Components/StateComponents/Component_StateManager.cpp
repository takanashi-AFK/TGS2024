#include "Component_StateManager.h"
#include "../../StageObject.h"
#include "PlayerState/PlayerState_Walk.h"


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
}

void Component_StateManager::Release()
{
}

void Component_StateManager::DrawData()
{
	// 状態を追加
	if (ImGui::SmallButton("Add State"))g_isAddStateWindowOpen = true;
	// 状態追加用ウィンドウ
	if (g_isAddStateWindowOpen)DrawAddStateWindow(this);

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

void Component_StateManager::DrawAddStateWindow(Component_StateManager* _stateManager) {
	// 名前を設定
	static char inputText[256] = {}; // バッファを定義
	ImGui::InputText("State Name", inputText, sizeof(inputText));

	// 状態の種類を選択するためのImGuiウィジェットを追加
	static int stateTypeIndex = 0;
	const char* stateTypes[] = { "Walking" }; // 状態のタイプ
	ImGui::Combo("State Type", &stateTypeIndex, stateTypes, IM_ARRAYSIZE(stateTypes));

	StateType selectedType = static_cast<StateType>(stateTypeIndex);

	// インスタンスができたら
	if (ImGui::Button("Confirm")) {
	// インスタンスを作成
	State* state = CreateState(selectedType, inputText);
		_stateManager->AddState(state);
		g_isAddStateWindowOpen = false;
	}
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

State* Component_StateManager::CreateState(StateType type, const string& name)
{
	switch (type) {
	case StateType::PLAYER_STATE_WALK:
		return new PlayerState_Walk(name, holder_);
		// 他の状態の生成
	default:
		return nullptr;
	}
}

State* Component_StateManager::GetCurrentState(string _key)
{
	return stateList_[_key];
}
