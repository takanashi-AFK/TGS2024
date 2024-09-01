#include "Scene_End.h"
#include "../Objects/UI/UIPanel.h"
#include "../../Engine/Global.h"
#include "../../Engine/ImGui/imgui.h"
#include "../Objects/UI/UIPanel.h"
#include "../Objects/UI/UIObject.h"
#include "../Objects/UI/UIText.h"

Scene_End::Scene_End(GameObject* parent_)
{
}

void Scene_End::Initialize()
{
	json loadData;

	if (JsonReader::Load("Datas/UILayouts/ResultScene_layout.json", loadData)) {

		// UIパネルを取得
		UIPanel* panel = UIPanel::GetInstance();
		panel->Load(loadData);
		UIText* text = (UIText*)panel->GetUIObject("ScoreNum");

		text->SetText(&ScoreManager::g_Score);

		// スプラッシュシーンのパネルlayoutを設定
	}
}

void Scene_End::Update()
{
	ImGui::Begin("result");
	ImGui::Text("time : %d",1234);
	ImGui::Text("score : %d", ScoreManager::GetScore());
	for (int i = 0; i < 13;i++)ImGui::NewLine();
	ImGui::Text("THANK YOU FOR PLAYING!");
	ImGui::End();



}

void Scene_End::Draw()
{
}

void Scene_End::Release()
{
}
