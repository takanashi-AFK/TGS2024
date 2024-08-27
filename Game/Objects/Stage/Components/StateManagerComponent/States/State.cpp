#include "State.h"

// �C���N���[�h
#include "State_Idle.h"
#include "State_Walk.h"
#include "../../../../../../Engine/ResourceManager/Model.h"
#include "../../../../../../Engine/ImGui/ImGui.h"
#include "../../../../../../Engine/Global.h"

State* CreateState(string _name, StateType _type, StageObject* _holder)
{
	switch (_type)
	{
	case Idle: return new State_Idle(_name,_holder);
	case Walk: return new State_Walk(_name,_holder);
	default: return nullptr;
	}
}

string StateTypeToString(StateType _type)
{
	switch (_type)
	{
	case Idle: return "Idle";
	case Walk: return "Walk";
	default: return "None";
	}
}

void State::ChildSave(json& _saveObj)
{
	_saveObj["name"] = name_;

	_saveObj["type"] = (int)type_;

	Save(_saveObj);
}

void State::ChildLoad(json& _loadObj)
{
	Load(_loadObj);
}

void State::ChildDrawData()
{
	// ���O��\��
	ImGui::Text("Name : %s", name_.c_str());
	
	// �^�C�v��\��
	ImGui::Text("Type : %s", StateTypeToString(type_).c_str());


	// ���f���ǉ��{�^��
	if (ImGui::Button("Add ModelData")){
		isAddModelWindowOpen_ = true;
	}

	// ���f���ǉ��E�B���h�E�̕\��
	if (isAddModelWindowOpen_)DrawAddModelWindow();

	// ���f���f�[�^���X�g��\��
	for (int i = 0; i < modelDataList_.size(); i++)
	{
		ImGui::Text("ModelData[%d]", i);
		ImGui::Text("FilePath : %s", modelDataList_[i].filePath.c_str());
		ImGui::Text("AnimFrameMax : %d", modelDataList_[i].animFrameMax);
		ImGui::Text("AnimFrameStart : %d", modelDataList_[i].animFrameStart);
		ImGui::Text("AnimSpeed : %f", modelDataList_[i].animSpeed);
	}

	DrawData();
}

void State::AddModelData(string _filePath, int _animFrameMax, int _animFrameStart, float _animSpeed)
{
	ModelData modelData;
	modelData.filePath = _filePath;
	modelData.animFrameMax = _animFrameMax;
	modelData.animFrameStart = _animFrameStart;
	modelData.animSpeed = _animSpeed;
	if(modelData.modelHandle < 0)modelData.Load();

	modelDataList_.push_back(modelData);
}

void State::DrawAddModelWindow()
{
	ImGui::Begin("Add ModelData", &isAddModelWindowOpen_);

	// ���݂̃t�@�C���p�X��\��
	static string filePath;
	ImGui::Text("imageFilePath_:%s", filePath.c_str());
	ImGui::SameLine();

	// �t�@�C���p�X���擾
	if (ImGui::SmallButton("...")) {
		// ���݂̃J�����g�f�B���N�g�����o���Ă���
		char defaultCurrentDir[MAX_PATH];
		GetCurrentDirectory(MAX_PATH, defaultCurrentDir);

		// �u�t�@�C�����J���v�_�C�A���O�̐ݒ�
		OPENFILENAME ofn; {
			TCHAR szFile[MAX_PATH] = {};
			ZeroMemory(&ofn, sizeof(ofn));
			ofn.lStructSize = sizeof(ofn);
			ofn.lpstrFile = szFile;
			ofn.lpstrFile[0] = '\0';
			ofn.nMaxFile = sizeof(szFile);
			ofn.lpstrFilter = TEXT("FBX�t�@�C��(*.fbx)\0 * .fbx\0���ׂẴt�@�C��(*.*)\0 * .*\0");
			ofn.nFilterIndex = 1;
			ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
			ofn.lpstrInitialDir = TEXT(".");
		}

		// �t�@�C���I���_�C�A���O�̕\��
		if (GetOpenFileName(&ofn) == TRUE) {
			// �t�@�C���p�X���擾
			filePath = ofn.lpstrFile;
			filePath = FileManager::GetAssetsRelativePath(filePath);
			FileManager::ReplaceBackslashes(filePath);
			SetCurrentDirectory(defaultCurrentDir);
		}
		else {
			ImGui::TreePop();
			return;
		}

		ImGui::TreePop();
	}
	static int animFrameMax = 0;
	ImGui::InputInt("AnimFrameMax", &animFrameMax);

	static int animFrameStart = 0;
	ImGui::InputInt("AnimFrameStart", &animFrameStart);

	static float animSpeed = 0.0f;
	ImGui::InputFloat("AnimSpeed", &animSpeed);

	if (ImGui::Button("Add"))
	{
		AddModelData(filePath, animFrameMax, animFrameStart, animSpeed);
	}

	ImGui::End();
}

void State::ModelData::Load()
{
	modelHandle = Model::Load(filePath);
}
