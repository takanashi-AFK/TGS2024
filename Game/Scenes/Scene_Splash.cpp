#include "Scene_Splash.h"

// インクルード
#include "../../Engine/Global.h"
#include "../../Engine/ResourceManager/Image.h"
#include "../../Engine/SceneManager.h"
#include "../Objects/UI/UIPanel.h"

// 定数
namespace {
	const float LIMIT_TIME = 1.f;				// シーンを切り替えるまでに掛かる時間（秒）
	const float IMAGE_REDUCTION_RATE = 0.67f;	// スプラッシュ画像の縮小倍率
}

Scene_Splash::Scene_Splash(GameObject* _parent)
	:GameObject(_parent,"Scene_Splash"),count_()
{
}

void Scene_Splash::Initialize()
{
	////// UIパネルの生成
	//UIPanel* pUIPanel = Instantiate<UIPanel>(this); {
	//	json uiData;
	//	if (JsonReader::Load("Datas/UILayouts/SplashScene.json", uiData))pUIPanel->Load(uiData);
	//}
}

void Scene_Splash::Update()
{
	//// n秒経過したらシーンを移動
	//if (count_ >= LIMIT_TIME * FPS)((SceneManager*)FindObject("SceneManager"))->ChangeScene(SCENE_ID_TITLE, TID_BLACKOUT);
	//
	//// カウントアップ
	//count_++;
}

void Scene_Splash::Draw()
{
}

void Scene_Splash::Release()
{
}
