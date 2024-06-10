#include "Scene_Play.h"

#include"../Objects/Stage/SkySphere.h"
#include"../Objects/Stage/Stage.h"
#include"../Otheres/StageEditor.h"
#include"../../Engine/ImGui/imgui.h"
#include"../Objects/Stage/Components/HealthManagerComponents/Component_HealthManager.h"
#include"../Objects/Stage/Components/BehaviorComponents/Component_PlayerBehavior.h"
#include"../../Engine/SceneManager.h"
Scene_Play::Scene_Play(GameObject* parent)
{
}

void Scene_Play::Initialize()
{
	Instantiate<SkySphere>(this);

	Stage* pStage = Instantiate<Stage>(this);

	// ステージを読み込み
	json stageData;
	JsonReader::Load("Datas/stage_Test00_sugawara.json", stageData);
	pStage->Load(stageData);
	
	vector<StageObject*>pSta;
	pStage->GetStageObjects();
   
#ifdef _DEBUG

	// ステージエディターを実行
	StageEditor* pSe = Instantiate<StageEditor>(this);
	
	// 編集対象を設定
	pSe->SetEditStage(pStage);

#endif // _DEBUG

}

void Scene_Play::Update()
{
	
	
	
	
}

void Scene_Play::Draw()
{
}

void Scene_Play::Release()
{
}
