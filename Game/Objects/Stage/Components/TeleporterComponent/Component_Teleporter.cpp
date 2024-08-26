#include "Component_Teleporter.h"
#include "../DetectorComponents/Component_CircleRangeDetector.h"
#include "../../StageObject.h"
#include "../../../../../Engine/GameObject/GameObject.h"
#include "../../../../../Engine/ImGui/imgui.h"
#include "../TimerComponent/Component_Timer.h"
#include "../../../../../Engine/Global.h"
#include "../MoveComponents/Component_InputMove.h"
#include "../../../../../Engine/Global.h"

namespace {
	EFFEKSEERLIB::EFKTransform t;/*������*/
}

Component_Teleporter::Component_Teleporter(string _name, StageObject* _holder, Component* _parent)
:Component(_holder, _name, Teleporter, _parent),isFirstEffect_(false)
{
}

void Component_Teleporter::Initialize()
{
	// �G�t�F�N�g�f�B���N�g�����X�L����
	std::string effectDirectory = "Effects";
	for (const auto& entry : fs::directory_iterator(effectDirectory))
	{
		if (entry.path().extension() == ".efk")
		{
			std::string effectName = entry.path().stem().string();
			effectNames_.push_back(effectName);
			EFFEKSEERLIB::gEfk->AddEffect(effectName.c_str(), entry.path().string().c_str());
		}
	}
	// �f�t�H���g�̃G�t�F�N�g��ݒ�
	if (!effectNames_.empty())
	{
		effectType_ = effectNames_[0];
	}
	// �q�R���|�[�l���g�̒ǉ�
	if (FindChildComponent("CircleRangeDetector") == false)AddChildComponent(CreateComponent("CircleRangeDetector", CircleRangeDetector, holder_, this));
	if (FindChildComponent("Timer") == false)AddChildComponent(CreateComponent("Timer", Timer, holder_, this));

	auto detector = dynamic_cast<Component_CircleRangeDetector*>(GetChildComponent("CircleRangeDetector"));
	if (detector == nullptr)return;

	
}

void Component_Teleporter::Update()
{
	if (target_ == nullptr)
		target_ = (StageObject*)holder_->FindObject(targetName_);
	if (target_ == nullptr)return;

	if (!isActive_)return;

	auto detector = dynamic_cast<Component_CircleRangeDetector*>(GetChildComponent("CircleRangeDetector"));
	if (detector == nullptr)return;
	auto timer = dynamic_cast<Component_Timer*>(GetChildComponent("Timer"));
	if (timer == nullptr)return;
	
	// ���o�Ώۂ̐ݒ�
	detector->SetTarget(target_);

	if (detector->IsContains()) {
		Teleport();
	}

	if (isTeleport_ == true) {
		// �^�C�}�[�J�n
		timer->SetTime(0.5f);
		timer->Start();

		// �^�C�}�[�I��
		if (timer->GetIsEnd()) {
			// �^�[�Q�b�g��WASD��T��(2�ȏ���Ă��Ȃ��z��)
			if (target_ != nullptr) {
				auto inputMove = target_->FindComponent(InputMove);
				if (inputMove.empty())return;
				for (auto iMove : inputMove) {
					iMove->Execute();
					break;
				}
			}
			timer->Reset();
			isTeleport_ = false;
		}
	}
}

void Component_Teleporter::Release()
{
}

void Component_Teleporter::Save(json& _saveObj)
{
	_saveObj["isActive_"] = isActive_;
	_saveObj["teleportPos_"] = { REFERENCE_XMFLOAT3(teleportPos_) };
	if (target_ != nullptr)
		_saveObj["target_"] = target_->GetObjectName();
	_saveObj["effectType_"] = effectType_;
	_saveObj["changeType_"] = changeType_;
}

void Component_Teleporter::Load(json& _loadObj)
{
	if (_loadObj.contains("isActive_"))isActive_ = _loadObj["isActive_"];
	if (_loadObj.contains("teleportPos_"))
		teleportPos_ = { _loadObj["teleportPos_"][0].get<float>(),_loadObj["teleportPos_"][1].get<float>(), _loadObj["teleportPos_"][2].get<float>() };
	if (_loadObj.contains("target_"))targetName_ = _loadObj["target_"];
	if (_loadObj.contains("effectType_"))effectType_ = _loadObj["effectType_"];
	if (_loadObj.contains("changeType_"))changeType_ = _loadObj["changeType_"];
}

void Component_Teleporter::DrawData()
{
	ImGui::Checkbox("isActive", &isActive_);
	ImGui::Combo("ChangeType", (int*)&changeType_, "CHANGE_TELEPORT\0CHANGE_SCENE\0CHANGE_JSON\0");

	if (changeType_ == CHANGE_TELEPORT) {
		ImGui::DragFloat3("TeleportPos", &teleportPos_.x, 0.1f);
	}
	else if (changeType_ == CHANGE_SCENE) {
		ImGui::InputInt("ChangeSceneID", (int*)&changeSceneID_);
	}
	else if (changeType_ == CHANGE_JSON) {
		if (ImGui::Button("...")) {
			//���݂̃J�����g�f�B���N�g�����o���Ă���
			char defaultCurrentDir[MAX_PATH];
			GetCurrentDirectory(MAX_PATH, defaultCurrentDir);

			// �ǉ�����I�u�W�F�N�g�̃��f���t�@�C���p�X��ݒ�
			{
				// �u�t�@�C�����J���v�_�C�A���O�̐ݒ�p�\���̂�ݒ�
				OPENFILENAME ofn; {
					TCHAR szFile[MAX_PATH] = {}; // �t�@�C�������i�[����o�b�t�@
					ZeroMemory(&ofn, sizeof(ofn)); // �\���̂̏�����
					ofn.lStructSize = sizeof(ofn); // �\���̂̃T�C�Y
					ofn.lpstrFile = szFile; // �t�@�C�������i�[����o�b�t�@
					ofn.lpstrFile[0] = '\0'; // ������
					ofn.nMaxFile = sizeof(szFile); // �t�@�C�����o�b�t�@�̃T�C�Y
					ofn.lpstrFilter = TEXT("json�t�@�C��(*.json)\0*.json\0���ׂẴt�@�C��(*.*)\0*.*\0"); // �t�B���^�[�iFBX�t�@�C���̂ݕ\���j
					ofn.nFilterIndex = 1; // �����I������t�B���^�[
					ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST; // �t���O�i�t�@�C�������݂��邱�ƁA�p�X�����݂��邱�Ƃ��m�F�j
					ofn.lpstrInitialDir = TEXT("."); // �J�����g�f�B���N�g���������I���ʒu�Ƃ��Đݒ�
				}

				// �t�@�C����I������_�C�A���O�̕\��
				if (GetOpenFileName(&ofn) == TRUE) {
					// �t�@�C���p�X���擾
					changeJsonPath_ = ofn.lpstrFile;

					// �J�����g�f�B���N�g������̑��΃p�X���擾
					changeJsonPath_ = FileManager::GetAssetsRelativePath(changeJsonPath_);

					// ���������"\\"��"/"�ɒu��
					FileManager::ReplaceBackslashes(changeJsonPath_);

					// �f�B���N�g����߂�
					SetCurrentDirectory(defaultCurrentDir);
				}
				else {
					return;
				}
			}
			ImGui::SameLine();
		}
		ImGui::Text(changeJsonPath_.c_str());
	}

	// �G�t�F�N�g�̑I��
	static int effectSelect = 0;

	// effectType_ �Ɋ�Â��ď����l��ݒ肷��
	auto it = std::find(effectNames_.begin(), effectNames_.end(), effectType_);
	if (it != effectNames_.end())
	{
		effectSelect = std::distance(effectNames_.begin(), it);
	}

	if (ImGui::BeginCombo("Effect", effectNames_[effectSelect].c_str()))
	{
		for (int i = 0; i < effectNames_.size(); ++i)
		{
			bool is_selected = (effectSelect == i);
			if (ImGui::Selectable(effectNames_[i].c_str(), is_selected))
			{
				effectSelect = i;
				effectType_ = effectNames_[i];
			}
			if (is_selected)
			{
				ImGui::SetItemDefaultFocus();
			}
		}
		ImGui::EndCombo();
	}

	//�Ώۂ̑I��
	vector<string> objNames;
	objNames.push_back("null");

	for (auto obj : ((Stage*)holder_->GetParent())->GetStageObjects())objNames.push_back(obj->GetObjectName());

	static int select = 0;

	// target_�̖��O�Ɋ�Â��ď����l��ݒ肷��
	if (target_ != nullptr) {
		string targetName = target_->GetObjectName();
		auto it = find(objNames.begin(), objNames.end(), targetName);
		if (it != objNames.end()) {
			select = distance(objNames.begin(), it);
		}
	}

	if (ImGui::BeginCombo("target_", objNames[select].c_str())) {
		for (int i = 0; i < objNames.size(); i++) {
			bool is_selected = (select == i);
			if (ImGui::Selectable(objNames[i].c_str(), is_selected)) select = i;
			if (is_selected) ImGui::SetItemDefaultFocus();
		}
		ImGui::EndCombo();
	}

	if (select == 0)target_ = nullptr;
	else target_ = (StageObject*)holder_->FindObject(objNames[select]);
}

void Component_Teleporter::Teleport()
{
	auto timer = dynamic_cast<Component_Timer*>(GetChildComponent("Timer"));
	if (timer == nullptr)return;
	static bool isEffectEnd = false;
	static bool isEffectNow = false;
	if (isEffectEnd == false) {

		target_->SetPosition(holder_->GetPosition());

		// �^�C�}�[�J�n
		timer->SetTime(1.f);
		timer->Start();

		// �^�[�Q�b�g��WASD��T��
		if (target_ != nullptr) {
			auto inputMove = target_->FindComponent(InputMove);
			if (inputMove.empty())return;
			for (auto iMove : inputMove) {
				iMove->Stop();
				break;
			}
		}

		if (timer->GetIsEnd()) {
			isEffectNow = true;
			timer->Reset();
		}

		if (isFirstEffect_ == false) {
		// effekseer: :Effect�̍Đ����̐ݒ�
		DirectX::XMStoreFloat4x4(&(t.matrix), holder_->GetWorldMatrix());/*������*/
		t.isLoop = false;/*������*/
		t.maxFrame = 60;/*������*/
		t.speed = 1.0f;/*������*/
		// effekseer: :Effect�̍Đ�
		mt = EFFEKSEERLIB::gEfk->Play(effectType_.c_str(), t);
		isFirstEffect_ = true;
		}
	}
	
	// �^�C�}�[�I��
	if (isEffectNow == true) {

		// ���o
		if (changeType_ == CHANGE_TELEPORT) {
			// teleportPos_�ւ̍��W�ύX
			target_->SetPosition(teleportPos_);
		}
		//else if (changeType_ == CHANGE_SCENE) {
		//	// ChangeSceneName_�ւ̃V�[���J��
		//	SceneManager* sceneManager = (SceneManager*)holder_->GetParent()->FindObject("SceneManager");
		//	sceneManager->ChangeScene(changeSceneID_, TID_BLACKOUT);
		//}
		else if (changeType_ == CHANGE_JSON) {
			// JSON�t�@�C���̓Ǎ�

			json loadData;
			if (JsonReader::Load(changeJsonPath_, loadData)) {
				// �X�e�[�W���쐬
				json loadObj;
				if (JsonReader::Load(changeJsonPath_, loadObj) == false) MessageBox(NULL, "�Ǎ��Ɏ��s���܂����B", 0, 0);
				((Stage*)holder_->GetParent())->Load(loadObj);
			}
		}
		isEffectNow = false;
		isTeleport_ = true;
		isFirstEffect_ = false;
	}


}

void Component_Teleporter::Execute(ChangeType _ch)
{
	isActive_ = true;
	changeType_ = _ch;
}
