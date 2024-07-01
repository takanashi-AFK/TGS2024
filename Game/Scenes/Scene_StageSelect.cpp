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
	UIButton* nextuibutton = (UIButton*)uipanel->GetUIObject("nextButton");
	
	//�{�^���������ꂽ�玟�̉摜�Ɉڍs�B
	if (nextuibutton->OnClick()) {

	}

	//���̃X�e�[�W�̉摜���N���b�N���ꂽ��v���C�V�[���Ɉڍs(�̂���json�t�@�C�����ǂݍ��݂���ēǂݍ��݂��ꂽ��v���C�V�[���Ɉڍs����)
	UIButton* stagebutton = (UIButton*)uipanel->GetUIObject("");
	if (stagebutton->OnClick()) {
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
