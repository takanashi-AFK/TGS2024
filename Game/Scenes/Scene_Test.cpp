#include "Scene_Test.h"

// インクルード
#include "../Objects/Stage/SkySphere.h"
#include "../Objects/UI/UIPanel.h"
#include "../Objects/Stage/Stage.h"
#include "../Otheres/GameEditor.h"

Scene_Test::Scene_Test(GameObject * parent)
	: GameObject(parent, "Scene_Test")
{
}

void Scene_Test::Initialize()
{
	// スカイスフィアの生成
	SkySphere* skySphere = Instantiate<SkySphere>(this);

	// UIパネルの生成
	UIPanel* uiPanel = Instantiate<UIPanel>(this); {
		json loadObj;
		JsonReader::Load("Datas/test_UIsave.json", loadObj);
		uiPanel->Load(loadObj);
	}

	// ステージを作成
	Stage* pStage = Instantiate<Stage>(this);
	
	// ステージを読み込み
	json stageData;
	JsonReader::Load("Datas/tkanaais.json", stageData);
	pStage->Load(stageData);


#ifdef _DEBUG
	// ゲームエディターの生成
	GameEditor* gameEditor = Instantiate<GameEditor>(this);
	gameEditor->SetEditStage(pStage);
	gameEditor->SetEditUIPanel(uiPanel);
#endif // _DEBUG
}

void Scene_Test::Update()
{
}

void Scene_Test::Draw()
{

}

void Scene_Test::Release()
{
}
