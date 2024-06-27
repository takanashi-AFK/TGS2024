#include "GameEditor.h"
#include "../../Engine/ImGui/imgui.h"
#include "../../Engine/DirectX/Direct3D.h"
#include "../Objects/Stage/Stage.h"
#include "../Objects/Stage/StageObject.h"
#include "../Objects/UI/UIPanel.h"
#include "../Objects/UI/UIObject.h"
#include "../../Engine/Global.h"
#include "../../Engine/DirectX/Texture.h"
#include "../../Engine/GameObject/Camera.h"
#include "../Objects/Camera/TPSCamera.h"
#include <algorithm> 

#ifdef min
#undef min
#endif

#ifdef max
#undef max
#endif

using namespace FileManager;

namespace {
	Texture* pTexture_camera = nullptr;
}


GameEditor::GameEditor(GameObject* _parent)
	:GameObject(_parent, "StageEditor"), editStage_(nullptr), selectEditStageObjectIndex_(-1), editUIPanel_(nullptr), selectEditUIObjectIndex_(-1), editType_(NONE)
{
}

void GameEditor::Initialize()
{
	// �J�����摜�̃e�N�X�`����ǂݍ���
	pTexture_camera = new Texture();
	pTexture_camera->Load("Images/GUI_Camera.png");

	// �J�����̈ʒu���擾
	cameraPosition_ = Camera::GetPosition();
	cameraTarget_ = Camera::GetTarget();
}

void GameEditor::Update()
{
}

void GameEditor::Draw()
{
	// ���[���h�A�E�g���C�i�[��`��
	DrawWorldOutLiner();

	// �ڍ׃E�B���h�E��`��
	DrawDatails();

	// UI�I�u�W�F�N�g�쐬�E�B���h�E��`��
	if(isShowCreateUIObjectWindow_)UIObjectClreateWindow();
}

void GameEditor::Release()
{
}

void GameEditor::DrawWorldOutLiner()
{
	// ImGui�ŕ\������E�B���h�E�̐ݒ���s��
	ImGui::SetNextWindowPos(ImVec2(Direct3D::screenWidth_ * 0.7f, 0));
	ImGui::SetNextWindowSize(ImVec2(Direct3D::screenWidth_ * 0.3f, Direct3D::screenHeight_ * 0.5f));

	// �Œ�E�B���h�E��\��
	ImGui::Begin("World Outliner", NULL,
		ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse| ImGuiWindowFlags_AlwaysHorizontalScrollbar);
	{
		ImGui::BeginTabBar("tab Ber");{

			// �X�e�[�W�I�u�W�F�N�g�̃^�u��\��
			if(editStage_ != nullptr)
				if (ImGui::BeginTabItem("StageObject")) {
					DrawStageOutLiner();
					editType_ = STAGE;
					ImGui::EndTabItem();
				}

			// UI�I�u�W�F�N�g�̃^�u��\��
			if(editUIPanel_ != nullptr)
				if (ImGui::BeginTabItem("UIPanel")) {
					DrawUIPanelOutLiner();
					editType_ = UIPANEL;
					ImGui::EndTabItem();
				}

			// �J�����̃^�u��\��
			if (ImGui::BeginTabItem("Camera")) {
				ImGui::Image(pTexture_camera->GetSRV(), ImVec2(16*23, 9*23));

				ImGui::Dummy(ImVec2(0, 10));
				// ���W�I�{�^��
				ImGui::Text("Camera type");
				if (ImGui::RadioButton("default camera", cameraType_ == DEFAULT))cameraType_ = DEFAULT;
				if (ImGui::RadioButton("tps camera", cameraType_ == TPS))cameraType_ = TPS;

				editType_ = CAMERA;
				ImGui::EndTabItem();
			}
		}
		ImGui::EndTabBar();
	}
	ImGui::End();
}

void GameEditor::DrawStageOutLiner()
{
	ImGui::Text("StageObject menu");

	if (ImGui::Button("Add"))AddStageObject();
	ImGui::SameLine();

	if (ImGui::Button("Save"))SaveStage();
	ImGui::SameLine();

	if (ImGui::Button("Load"))LoadStage();
	ImGui::SameLine();

	if (ImGui::Button("Delete"))editStage_->DeleteAllStageObject();

	ImGui::Separator();



	ImGui::BeginChild("ObjectList"); {
		auto& stageObjects = editStage_->GetStageObjects();
		for (int i = 0; i < stageObjects.size(); ++i) {
			if (ImGui::Selectable(stageObjects[i]->GetObjectName().c_str(), selectEditStageObjectIndex_ == i)) {
				selectEditStageObjectIndex_ = i;
			}

			// �h���b�O���J�n
			if (ImGui::BeginDragDropSource(ImGuiDragDropFlags_None)) {
				ImGui::SetDragDropPayload("DND_DEMO_CELL", &i, sizeof(int));  // int�^�̃C���f�b�N�X���y�C���[�h�Ƃ��Đݒ�
				ImGui::Text("Moving %s", stageObjects[i]->GetObjectName().c_str());
				ImGui::EndDragDropSource();
			}

			// �h���b�O���󂯓����
			if (ImGui::BeginDragDropTarget()) {
				if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("DND_DEMO_CELL")) {
					int payloadIndex = *(const int*)payload->Data;
					if (payloadIndex != i) {
						// �I�u�W�F�N�g�̏��Ԃ����ւ���
						auto temp = stageObjects[payloadIndex];
						if (payloadIndex < i) {
							// �ォ�牺�Ƀh���b�O
							for (int j = payloadIndex; j < i; ++j) {
								stageObjects[j] = stageObjects[j + 1];
							}
						}
						else {
							// �������Ƀh���b�O
							for (int j = payloadIndex; j > i; --j) {
								stageObjects[j] = stageObjects[j - 1];
							}
						}
						stageObjects[i] = temp;
						// �I���C���f�b�N�X�̍X�V
						if (selectEditStageObjectIndex_ == payloadIndex) {
							selectEditStageObjectIndex_ = i;
						}
						else if (selectEditStageObjectIndex_ >= std::min (i, payloadIndex) && selectEditStageObjectIndex_ <= std::max(i, payloadIndex)) {
							selectEditStageObjectIndex_ += (payloadIndex < i) ? -1 : 1;
						}
					}
				}
				ImGui::EndDragDropTarget();
			}
		}
	}
	ImGui::EndChild();

	
}

void GameEditor::DrawUIPanelOutLiner()
{
	ImGui::Text("UIObject menu");

	if (ImGui::Button("Add"))AddUIObject();
	ImGui::SameLine();

	if (ImGui::Button("Save"))SaveUIPanel();
	ImGui::SameLine();

	if (ImGui::Button("Load"))LoadUIPanel();
	ImGui::SameLine();

	if (ImGui::Button("Delete"))editUIPanel_->DeleteAllUIObject();

	ImGui::Separator();

	ImGui::BeginChild("ObjectList"); {
		// ���X�g��\��

		auto&& UIObjects = editUIPanel_->GetUIObjects();
		for (int i = 0; i < UIObjects.size(); ++i) {
			if (ImGui::Selectable(UIObjects[i]->GetObjectName().c_str(), selectEditUIObjectIndex_ == i)) {
				selectEditUIObjectIndex_ = i;
			}

			// �h���b�O���J�n
			if (ImGui::BeginDragDropSource(ImGuiDragDropFlags_None)) {
				ImGui::SetDragDropPayload("DND_DEMO_CELL", &i, sizeof(int));  // int�^�̃C���f�b�N�X���y�C���[�h�Ƃ��Đݒ�
				ImGui::Text("Moving %s", UIObjects[i]->GetObjectName().c_str());
				ImGui::EndDragDropSource();
			}

			// �h���b�O���󂯓����
			if (ImGui::BeginDragDropTarget()) {
				if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("DND_DEMO_CELL")) {
					int payloadIndex = *(const int*)payload->Data;
					if (payloadIndex != i) {
						// �I�u�W�F�N�g�̏��Ԃ����ւ���
						auto temp = UIObjects[payloadIndex];
						if (payloadIndex < i) {
							// �ォ�牺�Ƀh���b�O
							for (int j = payloadIndex; j < i; ++j) {
								UIObjects[j] = UIObjects[j + 1];
							}
						}
						else {
							// �������Ƀh���b�O
							for (int j = payloadIndex; j > i; --j) {
								UIObjects[j] = UIObjects[j - 1];
							}
						}
						UIObjects[i] = temp;
						// �I���C���f�b�N�X�̍X�V
						if (selectEditUIObjectIndex_ == payloadIndex) {
							selectEditUIObjectIndex_ = i;
						}
						else if (selectEditUIObjectIndex_ >= std::min(i, payloadIndex) && selectEditUIObjectIndex_ <= std::max(i, payloadIndex)) {
							selectEditUIObjectIndex_ += (payloadIndex < i) ? -1 : 1;
						}
					}
				}
				ImGui::EndDragDropTarget();
			}
		}
	}
	ImGui::EndChild();
}

void GameEditor::DrawDatails()
{
	// ImGui�ŕ\������E�B���h�E�̐ݒ���s��
	ImGui::SetNextWindowPos(ImVec2(Direct3D::screenWidth_ * 0.7f, Direct3D::screenHeight_ * 0.5f));
	ImGui::SetNextWindowSize(ImVec2(Direct3D::screenWidth_ * 0.3f, Direct3D::screenHeight_ * 0.5f));

	// �Œ�E�B���h�E��\��
	ImGui::Begin("Details", NULL,
				ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_AlwaysHorizontalScrollbar);
	{
		switch (editType_)
		{
		case STAGE:DrawStageObjectDatails(); break;
		case UIPANEL:DrawUIObjectDatails();break;
		case CAMERA:DrawDatalsCamera(); break;
		default:ImGui::Text("No information to display");break;
		}
	}
	ImGui::End();
}

void GameEditor::DrawStageObjectDatails()
{
	if (editStage_ == nullptr)return;

	if (selectEditStageObjectIndex_ >= 0 && selectEditStageObjectIndex_ < editStage_->GetStageObjects().size()) {

		editStage_->GetStageObjects()[selectEditStageObjectIndex_]->DrawData();
	}
	else ImGui::Text("No object selected");
}

void GameEditor::DrawUIObjectDatails()
{
	if (editUIPanel_ == nullptr)return;

	if (selectEditUIObjectIndex_ >= 0 && selectEditUIObjectIndex_ < editUIPanel_->GetUIObjects().size()) {

		editUIPanel_->GetUIObjects()[selectEditUIObjectIndex_]->ChildDrawData();
	}
	else ImGui::Text("No object selected");
}

void GameEditor::DrawDatalsCamera()
{
	ImGui::Text("Camera menu");
	switch (cameraType_)
	{
	case DEFAULT:
		tpsCamera_->SetActive(false);
		// �J�����̈ʒu��ݒ�
		ImGui::DragFloat3("Camera position", &cameraPosition_.x);
		// �J�����̏œ_��ݒ�
		ImGui::DragFloat3("Camera target", &cameraTarget_.x);
		// �J�����̈ʒu��ݒ�
		Camera::SetPosition(cameraPosition_);
		// �J�����̏œ_��ݒ�
		Camera::SetTarget(cameraTarget_);
		break;

	case TPS:
		// �ۑ��{�^��
		if (ImGui::Button("save")) {
			json saveObj;
			tpsCamera_->Save(saveObj);
			JsonReader::Save("Datas/CameraLayouts/TPSCamera.json", saveObj);
		}
		ImGui::SameLine();

		// �ǂݍ��݃{�^��
		if (ImGui::Button("load")) {
			json loadObj;
			JsonReader::Load("Datas/CameraLayouts/TPSCamera.json", loadObj);
			tpsCamera_->Load(loadObj);
		}

		ImGui::Separator();

		// �ݒ�p�̃E�B���h�E��\��
		tpsCamera_->DrawData();

		break;
	}
}

void GameEditor::UIObjectClreateWindow()
{
	static char nameBuffer[256] = "";
	if (isShowCreateUIObjectWindow_) {
		ImGui::Begin("Create UIObject", &isShowCreateUIObjectWindow_); {

			ImGui::NewLine();
			ImGui::Text("Set the details of the object to be generated!!");
			ImGui::Separator();

			// ���O�����
			ImGui::InputTextWithHint(":seting name", "Input object name...", nameBuffer, IM_ARRAYSIZE(nameBuffer));

			// �^�C�v��I��
			static UIType uitype = UIType::UI_NONE;	// �����I������
			static std::string type = "NONE";		// �����I������

			if (ImGui::BeginCombo(":seting type", type.c_str())) {
				for (int i = 0; i < UIType::UI_MAX; i++) {
					bool isSelected = (type == GetUITypeString((UIType)i));
					if (ImGui::Selectable(GetUITypeString((UIType)i).c_str(), isSelected)) {
						type = GetUITypeString((UIType)i);
						uitype = (UIType)i;
					}
					if (isSelected) {
						ImGui::SetItemDefaultFocus();
					}
				}
				ImGui::EndCombo();
			}

			// �����{�^��
			if (ImGui::Button("Create")) {
				// UI�I�u�W�F�N�g���쐬�E�ǉ�
				UIObject* obj = CreateUIObject(nameBuffer, uitype, editUIPanel_);
				if (obj != nullptr) {
					editUIPanel_->AddUIObject(obj);
					isShowCreateUIObjectWindow_ = false;
				}
			}
		}
		ImGui::End();
	}
}

void GameEditor::AddStageObject()
{
	// �ǉ�����I�u�W�F�N�g�̏�������ݒ�
	string name = "object" + std::to_string(editStage_->objects_.size());

	//���݂̃J�����g�f�B���N�g�����o���Ă���
	char defaultCurrentDir[MAX_PATH];
	GetCurrentDirectory(MAX_PATH, defaultCurrentDir);

	// �ǉ�����I�u�W�F�N�g�̃��f���t�@�C���p�X��ݒ�
	string filePath{}; {
		// �u�t�@�C�����J���v�_�C�A���O�̐ݒ�p�\���̂�ݒ�
		OPENFILENAME ofn; {
			TCHAR szFile[MAX_PATH] = {}; // �t�@�C�������i�[����o�b�t�@
			ZeroMemory(&ofn, sizeof(ofn)); // �\���̂̏�����
			ofn.lStructSize = sizeof(ofn); // �\���̂̃T�C�Y
			ofn.lpstrFile = szFile; // �t�@�C�������i�[����o�b�t�@
			ofn.lpstrFile[0] = '\0'; // ������
			ofn.nMaxFile = sizeof(szFile); // �t�@�C�����o�b�t�@�̃T�C�Y
			ofn.lpstrFilter = TEXT("FBX�t�@�C��(*.fbx)\0*.fbx\0���ׂẴt�@�C��(*.*)\0*.*\0"); // �t�B���^�[�iFBX�t�@�C���̂ݕ\���j
			ofn.nFilterIndex = 1; // �����I������t�B���^�[
			ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST; // �t���O�i�t�@�C�������݂��邱�ƁA�p�X�����݂��邱�Ƃ��m�F�j
			ofn.lpstrInitialDir = TEXT("."); // �J�����g�f�B���N�g���������I���ʒu�Ƃ��Đݒ�
		}

		// �t�@�C����I������_�C�A���O�̕\��
		if (GetOpenFileName(&ofn) == TRUE) {
			// �t�@�C���p�X���擾
			filePath = ofn.lpstrFile;

			// �J�����g�f�B���N�g������̑��΃p�X���擾
			filePath = GetAssetsRelativePath(filePath);

			// ���������"\\"��"/"�ɒu��
			ReplaceBackslashes(filePath);

			// �f�B���N�g����߂�
			SetCurrentDirectory(defaultCurrentDir);
		}
		else {
			return;
		}
	}

	// �I�u�W�F�N�g���쐬�E�ǉ�
	editStage_->AddStageObject(CreateStageObject(name, filePath, editStage_));
}

void GameEditor::SaveStage()
{
	//���݂̃J�����g�f�B���N�g�����o���Ă���
	char defaultCurrentDir[MAX_PATH];
	GetCurrentDirectory(MAX_PATH, defaultCurrentDir);

	// �ۑ���̃t�@�C���p�X���擾
	string filePath{}; {
		// �u�t�@�C����ۑ��v�_�C�A���O�̐ݒ�p�\���̂�ݒ�
		OPENFILENAME ofn; {
			ZeroMemory(&ofn, sizeof(ofn));
			ofn.lStructSize = sizeof(OPENFILENAME);
			ofn.lpstrFilter = TEXT("objectData(*.json)\0*.json\0���ׂẴt�@�C��(*.*)\0*.*\0\0");
			char fileName[MAX_PATH] = "����.json";
			ofn.lpstrFile = fileName;
			ofn.nMaxFile = MAX_PATH;
			ofn.Flags = OFN_OVERWRITEPROMPT;
			ofn.lpstrDefExt = "json";
			ofn.nFilterIndex = 1; // �����I������t�B���^�[
			ofn.lpstrInitialDir = TEXT("."); // �J�����g�f�B���N�g���������I���ʒu�Ƃ��Đݒ�
		}

		// �t�@�C����ۑ�����_�C�A���O�̕\��
		if (GetSaveFileName(&ofn) == TRUE) {
			// �t�@�C���p�X���擾
			filePath = ofn.lpstrFile;

			// �J�����g�f�B���N�g������̑��΃p�X���擾
			filePath = GetAssetsRelativePath(filePath);

			// ���������"\\"��"/"�ɒu��
			ReplaceBackslashes(filePath);

			// �f�B���N�g����߂�
			SetCurrentDirectory(defaultCurrentDir);
		}
		else {
			return;
		}
	}

	// �t�@�C���ɃX�e�[�W����ۑ�
	json saveObj;
	editStage_->Save(saveObj);
	if (JsonReader::Save(filePath, saveObj) == false) MessageBox(NULL, "�ۑ��Ɏ��s���܂����B", 0, 0);
	
}

void GameEditor::LoadStage()
{
	//���݂̃J�����g�f�B���N�g�����o���Ă���
	char defaultCurrentDir[MAX_PATH];
	GetCurrentDirectory(MAX_PATH, defaultCurrentDir);

	// �ǂݍ��ރt�@�C���̃p�X���擾
	string filePath{}; {
		// �u�t�@�C�����J���v�_�C�A���O�̐ݒ�p�\���̂�ݒ�
		OPENFILENAME ofn; {
			TCHAR szFile[MAX_PATH] = {}; // �t�@�C�������i�[����o�b�t�@
			ZeroMemory(&ofn, sizeof(ofn)); // �\���̂̏�����
			ofn.lStructSize = sizeof(ofn); // �\���̂̃T�C�Y
			ofn.lpstrFile = szFile; // �t�@�C�������i�[����o�b�t�@
			ofn.lpstrFile[0] = '\0'; // ������
			ofn.nMaxFile = sizeof(szFile); // �t�@�C�����o�b�t�@�̃T�C�Y
			ofn.lpstrFilter = TEXT("JSON�t�@�C��(*.json)\0*.json\0���ׂẴt�@�C��(*.*)\0*.*\0"); // �t�B���^�[�iFBX�t�@�C���̂ݕ\���j
			ofn.nFilterIndex = 1; // �����I������t�B���^�[
			ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST; // �t���O�i�t�@�C�������݂��邱�ƁA�p�X�����݂��邱�Ƃ��m�F�j
			ofn.lpstrInitialDir = TEXT("."); // �J�����g�f�B���N�g���������I���ʒu�Ƃ��Đݒ�
		}

		// �t�@�C����I������_�C�A���O�̕\��
		if (GetOpenFileName(&ofn) == TRUE) {
			// �t�@�C���p�X���擾
			filePath = ofn.lpstrFile;

			// �J�����g�f�B���N�g������̑��΃p�X���擾
			filePath = GetAssetsRelativePath(filePath);

			// ���������"\\"��"/"�ɒu��
			ReplaceBackslashes(filePath);

			// �f�B���N�g����߂�
			SetCurrentDirectory(defaultCurrentDir);
		}
		else {
			return;
		}
	}

	// �t�@�C����ǂݍ��݃X�e�[�W�𐶐�
	json loadObj;
	if (JsonReader::Load(filePath, loadObj) == false) MessageBox(NULL, "�Ǎ��Ɏ��s���܂����B", 0, 0);
	editStage_->Load(loadObj);
}

void GameEditor::AddUIObject()
{
	isShowCreateUIObjectWindow_ = true;
}

void GameEditor::SaveUIPanel()
{
	//���݂̃J�����g�f�B���N�g�����o���Ă���
	char defaultCurrentDir[MAX_PATH];
	GetCurrentDirectory(MAX_PATH, defaultCurrentDir);

	// �ۑ���̃t�@�C���p�X���擾
	string filePath{}; {
		// �u�t�@�C����ۑ��v�_�C�A���O�̐ݒ�p�\���̂�ݒ�
		OPENFILENAME ofn; {
			ZeroMemory(&ofn, sizeof(ofn));
			ofn.lStructSize = sizeof(OPENFILENAME);
			ofn.lpstrFilter = TEXT("objectData(*.json)\0*.json\0���ׂẴt�@�C��(*.*)\0*.*\0\0");
			char fileName[MAX_PATH] = "����.json";
			ofn.lpstrFile = fileName;
			ofn.nMaxFile = MAX_PATH;
			ofn.Flags = OFN_OVERWRITEPROMPT;
			ofn.lpstrDefExt = "json";
			ofn.nFilterIndex = 1; // �����I������t�B���^�[
			ofn.lpstrInitialDir = TEXT("."); // �J�����g�f�B���N�g���������I���ʒu�Ƃ��Đݒ�
		}

		// �t�@�C����ۑ�����_�C�A���O�̕\��
		if (GetSaveFileName(&ofn) == TRUE) {
			// �t�@�C���p�X���擾
			filePath = ofn.lpstrFile;

			// �J�����g�f�B���N�g������̑��΃p�X���擾
			filePath = GetAssetsRelativePath(filePath);

			// ���������"\\"��"/"�ɒu��
			ReplaceBackslashes(filePath);

			// �f�B���N�g����߂�
			SetCurrentDirectory(defaultCurrentDir);
		}
		else {
			return;
		}
	}

	// �t�@�C���ɃX�e�[�W����ۑ�
	json saveObj;
	editUIPanel_->Save(saveObj);
	if (JsonReader::Save(filePath, saveObj) == false) MessageBox(NULL, "�ۑ��Ɏ��s���܂����B", 0, 0);
}

void GameEditor::LoadUIPanel()
{
	//���݂̃J�����g�f�B���N�g�����o���Ă���
	char defaultCurrentDir[MAX_PATH];
	GetCurrentDirectory(MAX_PATH, defaultCurrentDir);

	// �ǂݍ��ރt�@�C���̃p�X���擾
	string filePath{}; {
		// �u�t�@�C�����J���v�_�C�A���O�̐ݒ�p�\���̂�ݒ�
		OPENFILENAME ofn; {
			TCHAR szFile[MAX_PATH] = {}; // �t�@�C�������i�[����o�b�t�@
			ZeroMemory(&ofn, sizeof(ofn)); // �\���̂̏�����
			ofn.lStructSize = sizeof(ofn); // �\���̂̃T�C�Y
			ofn.lpstrFile = szFile; // �t�@�C�������i�[����o�b�t�@
			ofn.lpstrFile[0] = '\0'; // ������
			ofn.nMaxFile = sizeof(szFile); // �t�@�C�����o�b�t�@�̃T�C�Y
			ofn.lpstrFilter = TEXT("JSON�t�@�C��(*.json)\0*.json\0���ׂẴt�@�C��(*.*)\0*.*\0"); // �t�B���^�[�iFBX�t�@�C���̂ݕ\���j
			ofn.nFilterIndex = 1; // �����I������t�B���^�[
			ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST; // �t���O�i�t�@�C�������݂��邱�ƁA�p�X�����݂��邱�Ƃ��m�F�j
			ofn.lpstrInitialDir = TEXT("."); // �J�����g�f�B���N�g���������I���ʒu�Ƃ��Đݒ�
		}

		// �t�@�C����I������_�C�A���O�̕\��
		if (GetOpenFileName(&ofn) == TRUE) {
			// �t�@�C���p�X���擾
			filePath = ofn.lpstrFile;

			// �J�����g�f�B���N�g������̑��΃p�X���擾
			filePath = GetAssetsRelativePath(filePath);

			// ���������"\\"��"/"�ɒu��
			ReplaceBackslashes(filePath);

			// �f�B���N�g����߂�
			SetCurrentDirectory(defaultCurrentDir);
		}
		else {
			return;
		}
	}

	// �t�@�C����ǂݍ��݃X�e�[�W�𐶐�
	json loadObj;
	if (JsonReader::Load(filePath, loadObj) == false) MessageBox(NULL, "�Ǎ��Ɏ��s���܂����B", 0, 0);
	editUIPanel_->Load(loadObj);
}
