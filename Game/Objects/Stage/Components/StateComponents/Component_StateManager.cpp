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

	// ���݂ǂ̏�ԂȂ̂��𔻒肵�AcurrentState�ɑ��
	for (auto* observer : observers_) {
		observer->OnStateChange(this);
	}

}

void Component_StateManager::Release()
{
}

void Component_StateManager::DrawData()
{
	// ��Ԃ�ǉ�
	if (ImGui::SmallButton("Add State"))isAddStateWindowOpen_ = true;
	// ��Ԓǉ��p�E�B���h�E
	if (isAddStateWindowOpen_)DrawAddStateWindow(this);

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

void Component_StateManager::DrawAddStateWindow(Component_StateManager* _stateManager) 
{

	ImGui::Begin("Add State..."); {

		// �X�e�[�g������
		static char stateName[256];
		ImGui::InputText("State Name", stateName, 256);

		// �X�e�[�g�^�C�v��I��
		// �^�C�v��I��
		static STATE_TYPE stateType = STATE_TYPE::None;	// �����I������
		static std::string type = "NONE";		// �����I������

		if (ImGui::BeginCombo(":seting type", type.c_str())) {
			for (int i = 0; i < STATE_TYPE::None; i++) {
				std::string uiTypeString = StateTypeToString((STATE_TYPE)i);
				if (uiTypeString.empty()) continue; // �󕶎���𖳎�

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

			// �X�e�[�g��ǉ�
			stateList_[stateName] = CreateState(stateName, stateType);

			// ���݂̃X�e�[�g�����݂��Ȃ��ꍇ�͒ǉ������X�e�[�g�����݂̃X�e�[�g�ɐݒ�
			if (currentState_ == nullptr) currentState_ = stateList_[stateName];

			// �E�B���h�E�����
			isAddStateWindowOpen_ = false;
		}
	}
	ImGui::End();
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

State* Component_StateManager::CreateState(string _name, STATE_TYPE _type)
{
	switch (_type)
	{
	case Idle: return new State_Idle(_name);
	default: return nullptr;
	}
	// ������else�łق��̏�Ԃ�ǉ�
}

State* Component_StateManager::GetCurrentState()
{
	return stateList_[currentStateKey_];
}
