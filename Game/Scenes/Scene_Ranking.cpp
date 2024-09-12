#include "Scene_Ranking.h"

// インクルード
#include "../Objects/UI/UIPanel.h"
#include "../Otheres/RankingManager.h"

Scene_Ranking::Scene_Ranking(GameObject* _parent)
	: GameObject(_parent, "Scene_Ranking")
{
}

void Scene_Ranking::Initialize()
{
	// UIパネルを取得
	UIPanel* panel = UIPanel::GetInstance();
	
	// UILayout_jsonファイルを読み込む
	json loadData;
	if (JsonReader::Load("Datas/UILayouts/rankingScene_layout.json", loadData)) panel->Load(loadData);
	
	// ランキングデータを読み込む
	RankingManager::GetInstance().Load("ranking.csv");
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
