#include "Scene_Splash.h"

// インクルード
#include "../../Engine/Global.h"
#include "../../Engine/SceneManager.h"
#include "../Objects/UI/UIPanel.h"

// 定数
namespace {
	const float LIMIT_TIME = 1.f;				// シーンを切り替えるまでに掛かる時間（秒）
}

Scene_Splash::Scene_Splash(GameObject* _parent)
	:GameObject(_parent,"Scene_Splash"),count_()
{
}

void Scene_Splash::Initialize()
{
	// jsonファイルを読み込む
	json loadData;
	if (JsonReader::Load("Datas/UILayouts/splashScene_layout.json", loadData)) {

		// UIパネルを取得
		UIPanel* panel = UIPanel::GetInstance();

		// スプラッシュシーンのパネルlayoutを設定
		panel->Load(loadData);
	}
}

void Scene_Splash::Update()
{
	// シーン切替処理
	{
		// 一定時間経過したらシーンを切り替える
		if (count_ >= LIMIT_TIME * FPS) {

			// シーンを切り替える
			SceneManager* sceneManager = (SceneManager*)FindObject("SceneManager");
			sceneManager->ChangeScene(SCENE_ID_TITLE,TID_BLACKOUT);

		}

		// 経過時間を加算
		count_++;
	}

}

void Scene_Splash::Draw()
{
}

void Scene_Splash::Release()
{
}
