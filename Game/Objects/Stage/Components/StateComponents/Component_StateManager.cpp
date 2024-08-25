#include "Component_StateManager.h"
#include "../../StageObject.h"
#include "PlayerState/PlayerState_Walk.h"


Component_StateManager::Component_StateManager(string _name, StageObject* _holder, Component* _parent)
	: Component(_holder, _name, StateManager,_parent)
{
}

void Component_StateManager::Initialize()
{
	// �e��Ԃ̏��������s��
	for (auto state : stateList_) {
		state.second->ChildInitialize();
	}
}

void Component_StateManager::Update()
{
	// ��Ԃ̕ύX���� //////
	if(currentStateKey_ != "") {
		// ��Ԃ��J�ډ\�ȏꍇ�J�ڂ���
		if (count_ >= changeLimit_) {
			currentStateKey_ = changeStateKey_;  // �ύX
			stateList_[currentStateKey_]->Start();
		}
		count_ += 1 / FPS;  // �J�E���g��i�߂�
	// �L�[�Ŏw�肳�ꂽ��Ԃ����݂��邩�ǂ������m�F���A���݂̏�Ԃ̍X�V���������s
	if (stateList_.find(currentStateKey_) != stateList_.end()) stateList_[currentStateKey_]->Update();
	}
}

void Component_StateManager::Release()
{
}

void Component_StateManager::DrawData()
{
	// ��Ԃ�ǉ�
	if (ImGui::SmallButton("Add State"))g_isAddStateWindowOpen = true;
	// ��Ԓǉ��p�E�B���h�E
	if (g_isAddStateWindowOpen)DrawAddStateWindow(this);

	// �ǉ�����Ă����Ԃ��c���[�m�[�h�ŕ\��
	if (ImGui::TreeNode("State list")) {
		// �����Ɍ��ݒǉ�����Ă���State��\��
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
	// ���O��ݒ�
	static char inputText[256] = {}; // �o�b�t�@���`
	ImGui::InputText("State Name", inputText, sizeof(inputText));

	// ��Ԃ̎�ނ�I�����邽�߂�ImGui�E�B�W�F�b�g��ǉ�
	static int stateTypeIndex = 0;
	const char* stateTypes[] = { "Walking" }; // ��Ԃ̃^�C�v
	ImGui::Combo("State Type", &stateTypeIndex, stateTypes, IM_ARRAYSIZE(stateTypes));

	StateType selectedType = static_cast<StateType>(stateTypeIndex);

	// �C���X�^���X���ł�����
	if (ImGui::Button("Confirm")) {
	// �C���X�^���X���쐬
	State* state = CreateState(selectedType, inputText);
		_stateManager->AddState(state);
		g_isAddStateWindowOpen = false;
	}
}

void Component_StateManager::Save(json& _saveObj)
{
	// �e��Ԃ̕ۑ�
	for (auto state : stateList_) {
		state.second->Save(_saveObj);
	}
	_saveObj["currentStateKey_"] = currentStateKey_;
}

void Component_StateManager::Load(json& _loadObj)
{
	// �e��Ԃ̓ǂݍ���
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
		// ���̏�Ԃ̐���
	default:
		return nullptr;
	}
}

State* Component_StateManager::GetCurrentState(string _key)
{
	return stateList_[_key];
}
