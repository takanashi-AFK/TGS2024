#include "Scene_Test.h"

// インクルード
#include "../Objects/Stage/SkySphere.h"
#include "../Objects/Stage/Stage.h"
#include "../Otheres/StageEditor.h"

Scene_Test::Scene_Test(GameObject * parent)
	: GameObject(parent, "Scene_Test")
{
}

void Scene_Test::Initialize()
{
	// スカイスフィアを標準で生成
	Instantiate<SkySphere>(this);

	// ステージを作成
	Stage* pStage = Instantiate<Stage>(this);
	
	// ステージを読み込み
	json stageData;
	JsonReader::Load("Datas/test_DebugStage01.json", stageData);
	pStage->Load(stageData);


#ifdef _DEBUG

	// ステージエディターを実行
	StageEditor* pSe = Instantiate<StageEditor>(this); 

	// 編集対象を設定
	pSe->SetEditStage(pStage);
	
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
