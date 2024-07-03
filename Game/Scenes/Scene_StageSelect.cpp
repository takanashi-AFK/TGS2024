#include "Scene_StageSelect.h"

//�C���N���[�h
#include"../../Engine/SceneManager.h"
#include "../../Engine/DirectX/Input.h"
#include "../Objects/UI/UIPanel.h"
#include "../Objects/UI/UIButton.h"
Scene_StageSelect::Scene_StageSelect(GameObject* parent)
: GameObject(parent, "Scene_StageSelect"), isSelectButtonMoving_(false),moveselectButton(0.0f)
{
}

void Scene_StageSelect::Initialize()
{
	uipanel = Instantiate<UIPanel>(this); 
	json uiData;
	if (JsonReader::Load("Datas/UILayouts/StageSelect.json", uiData)){
			uipanel->Load(uiData);
	}

	StageIndex = 0;

	stageImages.push_back(dynamic_cast<UIButton*>(uipanel->GetUIObject("StageSelectButton1")));
	stageImages.push_back(dynamic_cast<UIButton*>(uipanel->GetUIObject("StageSelectButton2")));

	
}

void Scene_StageSelect::Update()
{
	UIButton* stageSelectButton = stageImages[StageIndex];
	if (stageSelectButton == nullptr)return;
	if (stageSelectButton->OnClick()) {
		SceneManager* pChangeScene = (SceneManager*)FindObject("SceneManager");
		pChangeScene->ChangeScene(SCENE_ID_PLAY, TID_BLACKOUT);
	}

	//Button�������ꂽ�玟�̉摜�Ɉڍs
	UIButton* nextButton = dynamic_cast<UIButton*>(uipanel->GetUIObject("nextButton"));
	if (nextButton == nullptr)return;
	if (nextButton->OnClick()) {
		isSelectButtonMoving_ = true;
		
	}
	
	//Button�������ꂽ���O�̉摜�ɖ߂�
	UIButton* backButton = dynamic_cast<UIButton*>(uipanel->GetUIObject("backButton"));
	if (backButton == nullptr)return;
	if (backButton->OnClick()) {
		isSelectButtonMoving_ = true;
		
	}
	//true�ɂȂ��Ă����x�����Ɉړ���Button��
	if (isSelectButtonMoving_ == true) {
	    //stageSelectButton��x���W�����擾
		float selectButtonPos = stageSelectButton->GetPosition().x;

		selectButtonPos += moveselectButton;
		
		
		
	}

	



}

void Scene_StageSelect::Draw()
{
}

void Scene_StageSelect::Release()
{
}
