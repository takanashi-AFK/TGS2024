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
	if (currentState_ == nullptr)return;

	// �L�[�Ŏw�肳�ꂽ��Ԃ����݂��邩�ǂ������m�F���A���݂̏�Ԃ̍X�V���������s
	currentState_->Update();
	
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

	// ���݂̃X�e�[�g����\��
	ImGui::Text("currentState_: %s", currentState_ != nullptr ? currentState_->GetName().c_str() : "null");

	// �ǉ�����Ă����Ԃ��c���[�m�[�h�ŕ\��
	if (ImGui::TreeNode("State list")) {
		// �����Ɍ��ݒǉ�����Ă���State��\��
		for (auto state : stateList_) { 
			if (ImGui::TreeNode(state.second->GetName().c_str())) {

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
	// ���݂̃X�e�[�g����ۑ�
	_saveObj["currentStateName"] = currentState_ != nullptr ? currentState_->GetName() : "null";

	// �X�e�[�g���X�g��ۑ�
	for (auto state : stateList_) {
		json stateObj;
		state.second->ChildSave(stateObj);
		_saveObj["states"][state.first] = stateObj;
	}
}

void Component_StateManager::Load(json& _loadObj)
{

	// �X�e�[�g���X�g��Ǎ�
	for (auto state : _loadObj["states"].items()) {

		// �X�e�[�g�𐶐�
		State* s = CreateState(state.key(), (STATE_TYPE)state.value()["stateType_"].get<int>());

		if (s != nullptr) {
			s->ChildLoad(state.value());
			stateList_[state.key()] = s;
		}
	}

	// ���݂̃X�e�[�g����Ǎ�
	string currentStateName = _loadObj["currentStateName"].get<string>();
	currentState_ = stateList_[currentStateName];

	// ���݂̃X�e�[�g�����݂��Ȃ��ꍇ�̓X�e�[�g���X�g�̐擪�����݂̃X�e�[�g�ɐݒ�
	if (currentState_ == nullptr || !stateList_.empty()) currentState_ = stateList_.begin()->second;
}

State* Component_StateManager::CreateState(string _name, STATE_TYPE _type)
{
	switch (_type)
	{
	case Idle: return new State_Idle(_name);
	case Walk: return new PlayerState_Walk(_name);
	default: return nullptr;
	}
	// ������else�łق��̏�Ԃ�ǉ�
}

State* Component_StateManager::GetCurrentState()
{
	return currentState_;
}

State* Component_StateManager::GetState(STATE_TYPE _type)
{
	for (auto state : stateList_) {
		if (state.second->GetStateType() == _type)return state.second;
	}
	return nullptr;
}
