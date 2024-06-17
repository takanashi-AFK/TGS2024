#include "Scene_Title.h"

// インクルード
#include"../../Engine/SceneManager.h"
#include "../../Engine/DirectX/Input.h"

Scene_Title::Scene_Title(GameObject* parent)
	: GameObject(parent, "Scene_Title")
{
}

void Scene_Title::Initialize()
{
}

void Scene_Title::Update()
{
	// シーン移行
	if (Input::IsKeyDown(DIK_SPACE) ){
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
