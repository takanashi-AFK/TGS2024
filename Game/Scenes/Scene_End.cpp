#include "Scene_End.h"
#include "../Objects/UI/UIPanel.h"
#include "../../Engine/Global.h"
#include "../../Engine/ImGui/imgui.h"
#include "../Objects/UI/UIPanel.h"
#include "../Objects/UI/UIObject.h"
#include "../Objects/UI/UIText.h"
#include "../Objects/UI/UIButton.h"
#include "../../Engine/SceneManager.h"
#include "../Objects/Stage/SkySphere.h"
#include "../Objects/Stage/Stage.h"
#include "../Otheres/GameEditor.h"
#include "../Objects/Camera/TPSCamera.h"

Scene_End::Scene_End(GameObject* parent_)
{
}

void Scene_End::Initialize()
{
	json loadData;

	// スカイスフィアの生成
	SkySphere* skySphere = Instantiate<SkySphere>(this);


	// ステージを作成
	Stage* pStage = Instantiate<Stage>(this); {
		/*json stageData;
		JsonReader::Load("Datas/StageLayouts/stage_beta_00.json", stageData);
		pStage->Load(stageData);*/
	}


	if (JsonReader::Load("Datas/UILayouts/EndScene_layout.json", loadData)) {

		// UIパネルを取得
		panel = UIPanel::GetInstance();
		panel->Load(loadData);
		//UIText* text = (UIText*)panel->GetUIObject("ScoreNum");

		//text->SetText(&ScoreManager::g_Score);

		// スプラッシュシーンのパネルlayoutを設定
	}
	// TPSカメラの生成
	TPSCamera* tpsCamera = Instantiate<TPSCamera>(this);

#ifdef _DEBUG
	// ゲームエディターの生成
	GameEditor* gameEditor = Instantiate<GameEditor>(this);



	gameEditor->SetEditStage(pStage);


	// UIパネルの生成
	UIPanel* pUIPanel_ = UIPanel::GetInstance();
	gameEditor->SetEditUIPanel(pUIPanel_);


	gameEditor->SetTPSCamera(tpsCamera);

#endif // _DEBUG

}

void Scene_End::Update()
{
	UIButton* button = (UIButton*)panel->GetUIObject("SceneChangeButton");

	if (button->OnClick()) {
		SceneManager* sceneManager = (SceneManager*)FindObject("SceneManager");
		sceneManager->ChangeScene(SCENE_ID_TITLE, TID_BLACKOUT);
	}
}

void Scene_End::Draw()
{
}

void Scene_End::Release()
{
}
