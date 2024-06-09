#include "Scene_End.h"

#include"../Objects/UI/UIButton.h"
#include"../Objects/UI/UIPanel.h"
#include"../Objects/Stage/SkySphere.h"
#include"../../Engine/SceneManager.h"

Scene_End::Scene_End(GameObject* parent_)
{
}

void Scene_End::Initialize()
{
	Instantiate<SkySphere>(this);

	panel = Instantiate<UIPanel>(this);
	button = Instantiate<UIButton>(panel);
	panel->AddChild(button);
}

void Scene_End::Update()
{
	if (button->ClickButton()) {
		SceneManager* pChangeScene = (SceneManager*)FindObject("SceneManager");
		pChangeScene->ChangeScene(SCENE_ID_TITLE, TID_BLACKOUT);
	}
}

void Scene_End::Draw()
{
}

void Scene_End::Release()
{
}
