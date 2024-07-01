#include "Scene_StageSelect.h"

//インクルード
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
	
	//ボタンが押されたら次の画像に移行。
	if (nextuibutton->OnClick()) {

	}

	//そのステージの画像がクリックされたらプレイシーンに移行(のちにjsonファイルが読み込みされて読み込みされたらプレイシーンに移行する)
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
