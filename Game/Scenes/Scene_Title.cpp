#include "Scene_Title.h"

// インクルード
#include"../../Engine/SceneManager.h"
#include "../../Engine/DirectX/Input.h"
#include "../Objects/UI/UIPanel.h"
#include "../Objects/UI/UIButton.h"

Scene_Title::Scene_Title(GameObject* parent)
	: GameObject(parent, "Scene_Title")
{
}

void Scene_Title::Initialize()
{
	//// UIパネルの生成
	pUIPanel_ = Instantiate<UIPanel>(this); {
		json uiData;
		if(JsonReader::Load("Datas/UILayouts/TitleScene.json", uiData))pUIPanel_->Load(uiData);
	}
}

void Scene_Title::Update()
{
	// ボタンが押されたらプレイシーンに移行
	UIButton* button = (UIButton*)pUIPanel_->GetUIObject("02StartButton");
	if (button == nullptr)return;
	if (button->OnClick()) {
		SceneManager* pChangeScene = (SceneManager*)FindObject("SceneManager");
		pChangeScene->ChangeScene(SCENE_ID_PLAY, TID_BLACKOUT);
	}
}

void Scene_Title::Draw()
{
}

void Scene_Title::Release()
{
}
