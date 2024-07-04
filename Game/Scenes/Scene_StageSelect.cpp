#include "Scene_StageSelect.h"

//�C���N���[�h
#include"../../Engine/SceneManager.h"
#include "../../Engine/DirectX/Input.h"
#include "../Objects/UI/UIPanel.h"
#include "../Objects/UI/UIButton.h"
#include"../../Engine/ImGui/imgui.h"
#include"../../Engine/DirectX/Direct3D.h"
Scene_StageSelect::Scene_StageSelect(GameObject* parent)
	: GameObject(parent, "Scene_StageSelect"), isSelectButtonMoving_(false), moveselectButton(0.f),maxButtonmove_(0.f),StageIndex(0),MoveButtonDistance_(0.f),easingfunc_()
{
}

void Scene_StageSelect::Initialize()
{
	//UI�p�l�����쐬
	uipanel = Instantiate<UIPanel>(this);
	//uiData��json�t�@�C�������݂����̂ł����uipanel�ɕۑ�����Ă���
	json uiData;
	if (JsonReader::Load("Datas/UILayouts/StageSelect.json", uiData)) {
		uipanel->Load(uiData);
	}

	stageImages.push_back(dynamic_cast<UIButton*>(uipanel->GetUIObject("StageSelectButton1")));
	stageImages.push_back(dynamic_cast<UIButton*>(uipanel->GetUIObject("StageSelectButton2")));
}

void Scene_StageSelect::Update()
{
#ifdef _DEBUG
	if (ImGui::BeginCombo("EaseFunc", easingfunc_.c_str())) {
		for (const auto& pair : Direct3D::EaseFunc) {
			bool isSelected = (easingfunc_ == pair.first);
			if (ImGui::Selectable(pair.first.c_str(), isSelected)) {
				easingfunc_ = pair.first; // Set the selected ease function
			}
			if (isSelected) {
				ImGui::SetItemDefaultFocus(); // Ensure the selected item is focused
			}
		}
		ImGui::EndCombo();
	}

#endif // DEBUG

	maxButtonmove_ = 3.f;
	//stageSelectButton�������ꂽ��V�[���Ɉړ�
	UIButton* stageSelectButton = stageImages[StageIndex];
	if (stageSelectButton == nullptr)return;
	if (stageSelectButton->OnClick()) {
		SceneManager* pChangeScene = (SceneManager*)FindObject("SceneManager");
		pChangeScene->ChangeScene(SCENE_ID_PLAY, TID_BLACKOUT);
	}

	//Button�������ꂽ�玟�̉摜�Ɉڍs
	UIButton* nextButton = dynamic_cast<UIButton*>(uipanel->GetUIObject("NextButton"));
	if (nextButton == nullptr)return;
	if (nextButton->OnClick()) {
		moveselectButton = 0.01;
		isSelectButtonMoving_ = true;
		StageIndex = (StageIndex + 1) % stageImages.size();
	}
	
	//Button�������ꂽ��-�����Ɉړ����摜�����ւ���
	UIButton* backButton = dynamic_cast<UIButton*>(uipanel->GetUIObject("BuckButton"));
	if (backButton == nullptr)return;
	if (backButton->OnClick()) {
		isSelectButtonMoving_ = true;
		moveselectButton = -0.01;
		StageIndex = (StageIndex - 1+stageImages.size()) % stageImages.size();
	}

	//true�ɂȂ��Ă����x������Button���ړ�������
	if (isSelectButtonMoving_) {
		for (int i = 0; i < stageImages.size(); ++i) {
			stageSelectButton = stageImages[i];
			//stageSelectButton��x���W�����擾
			float selectButtonPos = stageSelectButton->GetPosition().x;

			//MoveButtonDistance_ = 2.f;
			//Button��x���W�X�V
			selectButtonPos += moveselectButton;

			// �ʒu�X�V
			stageSelectButton->SetPosition({ selectButtonPos, stageSelectButton->GetPosition().y,stageSelectButton->GetPosition().z });

			//�w�肵�������ړ�������isSelectButtonMoving��false�ɂ���
			if ((moveselectButton > 0 && selectButtonPos >= maxButtonmove_) ||
				(moveselectButton < 0 && selectButtonPos <= -maxButtonmove_)) {
				isSelectButtonMoving_ = false;
				moveselectButton = 0;
				//MoveButtonDistance_ = 0;
			}



		}
	}
	/*for (size_t i = 0; i < stageImages.size(); ++i)
	{
		UIButton* button = stageImages[i];
		if (button != nullptr)
		{
			ImGui::Text("Button %zu Pos: %.2f", i, button->GetPosition().x);
		}
	}*/
	
}


void Scene_StageSelect::Draw()
{
}

void Scene_StageSelect::Release()
{
}
