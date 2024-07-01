#include "Scene_StageSelect.h"

//�C���N���[�h
#include"../../Engine/SceneManager.h"
#include "../../Engine/DirectX/Input.h"
#include "../Objects/UI/UIPanel.h"
#include "../Objects/UI/UIButton.h"
Scene_StageSelect::Scene_StageSelect(GameObject* parent)
: GameObject(parent, "Scene_StageSelect")
{
}

void Scene_StageSelect::Initialize()
{
	uipanel = Instantiate<UIPanel>(this); 
}

void Scene_StageSelect::Update()
{
	
	//2�̃X�e�[�W�̉摜��\���B
	UIButton* stageselectButton1 = (UIButton*)uipanel->GetUIObject("stageselectButton1");
	if (stageselectButton1 == nullptr)return;
	if (stageselectButton1->OnClick()) {
		SceneManager* pChangeScene = (SceneManager*)FindObject("SceneManager");
		pChangeScene->ChangeScene(SCENE_ID_PLAY, TID_BLACKOUT);
	}

	UIButton*stageselectButton2 =(UIButton*)uipanel->GetUIObject("stageselectButton2");
	if (stageselectButton2 == nullptr)return;
	if (stageselectButton2->OnClick()) {
			SceneManager* pChangeScene = (SceneManager*)FindObject("SceneManager");
			pChangeScene->ChangeScene(SCENE_ID_PLAY, TID_BLACKOUT);
	}
}

void Scene_StageSelect::Draw()
{
}

void Scene_StageSelect::Release()
{
}
