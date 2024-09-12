#include "Scene_Ranking.h"

// インクルード
#include "../Objects/UI/UIPanel.h"

Scene_Ranking::Scene_Ranking(GameObject* _parent)
	: GameObject(_parent, "Scene_Ranking")
{
}

void Scene_Ranking::Initialize()
{
	// UILayout_jsonファイルを読み込む
	json loadData;
	if (JsonReader::Load("Datas/UILayouts/rankingScene_layout.json", loadData)) {

		// UIパネルを取得
		UIPanel* panel = UIPanel::GetInstance();

		// スプラッシュシーンのパネルlayoutを設定
		panel->Load(loadData);
	}
}

void Scene_Ranking::Update()
{
}

void Scene_Ranking::Draw()
{
}

void Scene_Ranking::Release()
{
}
