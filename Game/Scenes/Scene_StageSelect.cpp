#include "Scene_StageSelect.h"

//�C���N���[�h
#include"../../Engine/SceneManager.h"
#include "../../Engine/DirectX/Input.h"
#include "../Objects/UI/UIPanel.h"
#include "../Objects/UI/UIButton.h"
#include"../../Engine/ImGui/imgui.h"
#include"../../Engine/DirectX/Direct3D.h"
Scene_StageSelect::Scene_StageSelect(GameObject* parent)
	: GameObject(parent, "Scene_StageSelect"), isSelectButtonMoving_(false), moveselectButton(0.f),maxButtonmove_(0.f),StageIndex(0),easingfunc_()
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
	//-------Imgui�ł��[���񂮊֐���I�Ԃ��ƂœK�p�����Stage��Image�摜������-------
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

	//---------�X�e�[�W�I����ʂ��X�N���[�����ňړ�����悤�ɂ���-----------------------------------
	maxButtonmove_ = 1.5f;
	
	//stageSelectButton�������ꂽ��Play�V�[���Ɉړ�
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
		isSelectButtonMoving_ = true;
		
		StageIndex = (StageIndex + 1) % stageImages.size();
	}
	
	//Button�������ꂽ��-�����Ɉړ����摜�����ւ���
	UIButton* buckButton = dynamic_cast<UIButton*>(uipanel->GetUIObject("BuckButton"));
	if (buckButton == nullptr)return;
	if (buckButton->OnClick()) {
		//isSelectButtonMoving��true�ɂ���
		isSelectButtonMoving_ = true;

		StageIndex = (StageIndex - 1 + stageImages.size()) % stageImages.size();
	}

	//true�ɂȂ��Ă����StageImage���X�N���[�����ɓ���
	if (isSelectButtonMoving_ == true) {
		for (int i = 0; i < stageImages.size(); ++i) {
			stageSelectButton = stageImages[i];

			float selectButtonPos = stageSelectButton->GetPosition().x;

			moveselectButton += 0.01;

			selectButtonPos = moveselectButton;

			// �ʒu�X�V
			stageSelectButton->SetPosition({selectButtonPos, stageSelectButton->GetPosition().y, stageSelectButton->GetPosition().z });
			
		}
	}
	if (moveselectButton >=maxButtonmove_) {
		isSelectButtonMoving_ = false;
		moveselectButton = 0;
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
