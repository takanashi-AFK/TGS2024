#include "Scene_StageSelect.h"

//�C���N���[�h
#include"../../Engine/SceneManager.h"
#include "../../Engine/DirectX/Input.h"
#include "../Objects/UI/UIPanel.h"
#include "../Objects/UI/UIButton.h"
Scene_StageSelect::Scene_StageSelect(GameObject* parent)
	: GameObject(parent, "Scene_StageSelect"), isSelectButtonMoving_(false), moveselectButton(0.f),maxButtonmove_(0.f),StageIndex(0)
{
}

void Scene_StageSelect::Initialize()
{
	uipanel = Instantiate<UIPanel>(this);
	json uiData;
	if (JsonReader::Load("Datas/UILayouts/StageSelect.json", uiData)) {
		uipanel->Load(uiData);
	}

	stageImages.push_back(dynamic_cast<UIButton*>(uipanel->GetUIObject("StageSelectButton1")));
	stageImages.push_back(dynamic_cast<UIButton*>(uipanel->GetUIObject("StageSelectButton2")));
}

void Scene_StageSelect::Update()
{
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
	}

	//Button�������ꂽ��-�����Ɉړ����摜�����ւ���
	UIButton* backButton = dynamic_cast<UIButton*>(uipanel->GetUIObject("BuckButton"));
	if (backButton == nullptr)return;
	if (backButton->OnClick()) {
		isSelectButtonMoving_ = true;
		moveselectButton = -0.01;
	}
	//true�ɂȂ��Ă����x������Button���ړ�������
	if (isSelectButtonMoving_ == true) {
		//stageSelectButton��x���W�����擾
		float selectButtonPos = stageSelectButton->GetPosition().x;

		//Button��x���W�X�V
		//selectButtonPos = Direct3D::EaseFunc[easingfunc_](moveselectButton);
		selectButtonPos += moveselectButton;
		// �ʒu�X�V
		stageSelectButton->SetPosition({ selectButtonPos, stageSelectButton->GetPosition().y,stageSelectButton->GetPosition().z });

		//�w�肵�������ړ�������isSelectButtonMoving��false�ɂ���
	
	}
}


void Scene_StageSelect::Draw()
{
}

void Scene_StageSelect::Release()
{
}
