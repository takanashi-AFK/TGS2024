#include "Component_StateManager.h"

// �C���N���[�h�f�B���N�e�B�u
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
	// ���݂̃X�e�[�g�����݂��Ȃ��ꍇ�͏������s��Ȃ�
	if (currentState_ == nullptr)return;

	// ���݂̃X�e�[�g���X�V
	currentState_->Update();

	// �X�e�[�g�ύX�ʒm
	for (auto observer : observers_) {
		observer->OnStateChange(this);
	}
}

void Component_StateManager::Release()
{
}

void Component_StateManager::Save(json& _saveObj)
{
	// ���݂̃X�e�[�g����ۑ�
	_saveObj["currentStateName"] = currentState_ != nullptr ? currentState_->GetName() : "null";

	// �X�e�[�g���X�g��ۑ�
	for (auto state : states_) {
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
		State* s = CreateState(state.key(), (StateType)state.value()["type"].get<int>(),holder_);

		if(s != nullptr){
			s->ChildLoad(state.value());
			states_[state.key()] = s;
		}
	}

	// ���݂̃X�e�[�g����Ǎ�
	string currentStateName = _loadObj["currentStateName"].get<string>();
	currentState_ = states_[currentStateName];

	// ���݂̃X�e�[�g�����݂��Ȃ��ꍇ�̓X�e�[�g���X�g�̐擪�����݂̃X�e�[�g�ɐݒ�
	if (currentState_ == nullptr || !states_.empty() ) currentState_ = states_.begin()->second;
}

void Component_StateManager::DrawData()
{
	// ���݂̃X�e�[�g����\��
	ImGui::Text("currentState_: %s",currentState_ != nullptr ? currentState_->GetName().c_str() : "null");

	// �X�e�[�g���X�g��\��
	if(ImGui::TreeNode("states_")) {

		// �X�e�[�g�ǉ��{�^����\��
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

	// �X�e�[�g�ǉ��E�B���h�E��\��
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

		// �X�e�[�g������
		static char stateName[256];
		ImGui::InputText("State Name", stateName, 256);

		// �X�e�[�g�^�C�v��I��
		// �^�C�v��I��
		static StateType stateType = StateType::None;	// �����I������
		static std::string type = "NONE";		// �����I������

		if (ImGui::BeginCombo(":seting type", type.c_str())) {
			for (int i = 0; i < StateType::None; i++) {
				std::string uiTypeString = StateTypeToString((StateType)i);
				if (uiTypeString.empty()) continue; // �󕶎���𖳎�

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
			
			// �X�e�[�g��ǉ�
			states_[stateName] = CreateState(stateName, stateType,holder_);

			// ���݂̃X�e�[�g�����݂��Ȃ��ꍇ�͒ǉ������X�e�[�g�����݂̃X�e�[�g�ɐݒ�
			if (currentState_ == nullptr) currentState_ = states_[stateName];
			
			// �E�B���h�E�����
			isAddStateWindowOpen_ = false;
		}
	}
	ImGui::End();
}
