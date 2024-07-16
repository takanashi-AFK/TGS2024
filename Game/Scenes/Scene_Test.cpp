#include "Scene_Test.h"

// インクルード
#include "../Objects/Stage/SkySphere.h"
#include "../Objects/UI/UIPanel.h"
#include "../Objects/Stage/Stage.h"
#include "../Otheres/GameEditor.h"
#include "../../Engine/GameObject/Camera.h"
#include "../../Engine/Global.h"
#include "../Objects/Camera/TPSCamera.h"


Scene_Test::Scene_Test(GameObject * parent)
	: GameObject(parent, "Scene_Test")
{
}

void Scene_Test::Initialize()
{
	// スカイスフィアの生成
	SkySphere* skySphere = Instantiate<SkySphere>(this);

	// ステージを作成
	Stage* pStage = Instantiate<Stage>(this); {
		json stageData;
		JsonReader::Load("Datas/efectTest.json", stageData);
		pStage->Load(stageData);
	}

// デフォルトカメラ情報の読み込み
json camData;
if (JsonReader::Load("Datas/CameraLayouts/camera.json", camData)) {
    Camera::SetPosition(JFLOAT3(camData["position"]));
    Camera::SetTarget(JFLOAT3(camData["target"]));
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

void Scene_Test::Update()
{
}

void Scene_Test::Draw()
{
}

void Scene_Test::Release()
{
	json camData;
	camData["position"] = { REFERENCE_XMFLOAT3(Camera::GetPosition()) };
	camData["target"] = { REFERENCE_XMFLOAT3(Camera::GetTarget()) };
	JsonReader::Save("Datas/CameraLayouts/camera.json", camData);
}
