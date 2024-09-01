#include "Scene_End.h"
#include "../Objects/UI/UIPanel.h"
#include "../../Engine/Global.h"
#include "../../Engine/ImGui/imgui.h"
#include "../Objects/UI/UIPanel.h"
#include "../Objects/UI/UIObject.h"
#include "../Objects/UI/UIText.h"
#include "../Objects/UI/UIButton.h"
#include "../../Engine/SceneManager.h"

Scene_End::Scene_End(GameObject* parent_)
{
}

void Scene_End::Initialize()
{
	json loadData;

	if (JsonReader::Load("Datas/UILayouts/ResultScene_layout.json", loadData)) {

		// UIパネルを取得
		panel = UIPanel::GetInstance();
		panel->Load(loadData);
		UIText* text = (UIText*)panel->GetUIObject("ScoreNum");

		text->SetText(&ScoreManager::g_Score);

		// スプラッシュシーンのパネルlayoutを設定
	}
}

void Scene_End::Update()
{
	UIButton* button = (UIButton*)panel->GetUIObject("NextSceneButton");

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
