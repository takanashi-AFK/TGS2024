#include "Scene_End.h"
#include "../../Engine/ResourceManager/Image.h"
#include "../../Engine/SceneManager.h"

Scene_End::Scene_End(GameObject* parent_)
{
}

void Scene_End::Initialize()
{
	imageHandle_ = Image::Load("Images/EndScene/EndSceneImage.png");
	assert(imageHandle_ >= -1);
}

void Scene_End::Update()
{
	static int count = 0;
	

	if (count > 180) {
		SceneManager* sceneManager = (SceneManager*)FindObject("SceneManager");
		sceneManager->ChangeScene(SCENE_ID_TITLE, TID_BLACKOUT);
	}
	count++;
}

void Scene_End::Draw()
{
	Image::SetTransform(imageHandle_, transform_);
	Image::Draw(imageHandle_);
}

void Scene_End::Release()
{
}
