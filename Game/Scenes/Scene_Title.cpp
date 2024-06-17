#include "Scene_Title.h"

#include"../../Game/Objects/UI/UIPanel.h"
#include"../../Game/Objects/UI/UIButton.h"
#include"../../Engine/ResourceManager/Image.h"
#include"../../Engine/SceneManager.h"
Scene_Title::Scene_Title(GameObject* parent)
	: GameObject(parent, "Scene_Title"),panel_(nullptr),button_(nullptr)
{
}

void Scene_Title::Initialize()
{
	panel_ = Instantiate<UIPanel>(this);
	button_ = Instantiate<UIButton>(panel_);
	panel_->AddChild(button_);
}

void Scene_Title::Update()
{
	//ボタンが押されたらプレイシーンに移行
	if (button_->ClickButton()) {
		SceneManager* pChangePlay = (SceneManager*)FindObject("SceneManager");
		pChangePlay->ChangeScene(SCENE_ID_PLAY);
	}
}

void Scene_Title::Draw()
{
}

void Scene_Title::Release()
{
}
