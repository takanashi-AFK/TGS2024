#include "Scene_Title.h"

#include"../../Game/Objects/UI/UIPanel.h"
#include"../../Game/Objects/UI/UIButton.h"
#include"../../Engine/ResourceManager/Image.h"
#include"../../Engine/SceneManager.h"
Scene_Title::Scene_Title(GameObject* parent)
	: GameObject(parent, "Scene_Title"),panel(nullptr),button(nullptr)
{
}

void Scene_Title::Initialize()
{
	panel = Instantiate<UIPanel>(this);
	button = Instantiate<UIButton>(panel);
	panel->AddChild(button);
}

void Scene_Title::Update()
{
	if (button->ClickButton()) {
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
