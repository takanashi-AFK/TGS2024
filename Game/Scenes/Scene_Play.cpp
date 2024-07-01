#include "Scene_Play.h"

// インクルード
#include"../Objects/Stage/SkySphere.h"
#include"../Objects/Stage/Stage.h"
#include "../Objects/UI/UIPanel.h"
#include"../Objects/Stage/Components/HealthManagerComponents/Component_HealthManager.h"
#include"../Objects/Stage/Components/BehaviorComponents/Component_PlayerBehavior.h"
#include"../../Engine/SceneManager.h"
#include "../Objects/UI/UIButton.h"
#include "../Objects/Camera/TPSCamera.h"

Scene_Play::Scene_Play(GameObject* parent)
{
}

void Scene_Play::Initialize()
{
	// スカイスフィアを生成
	Instantiate<SkySphere>(this);

	// ステージを生成
	Stage* pStage = Instantiate<Stage>(this); {
		// ステージを読み込み
		json stageData;
		JsonReader::Load("Datas/StageLayouts/stage_Test00_sugawara.json", stageData);
		pStage->Load(stageData);
	}
	//	//範囲for分でオブジェクトリストの取得
	//	for (auto pList : pStage->GetStageObjects()) {
	//		//リスト内でとうろくされているPlayerBehaviorがあったらコンポーネントをキャストして代入
	//		if (pList->FindComponent("PlayerBehavior")) {
	//			Component_PlayerBehavior* playerBeha = dynamic_cast<Component_PlayerBehavior*>(pList->FindComponent("PlayerBehavior"));
	//			if (playerBeha != nullptr) {
	//				//playerBehaから子コンポーネントを取得する
	//				playerHealth_ = dynamic_cast<Component_HealthManager*>(playerBeha->GetChildComponent("HealthManager"));
	//			}
	//		}
	//	}
	//}

	//TPSCamera* tpsCamera = Instantiate<TPSCamera>(this); {
	//	json camData;
	//	if (JsonReader::Load("Datas/CameraLayouts/TPSCamera.json", camData)) {
	//		tpsCamera->Load(camData);
	//	}
	//}
}

void Scene_Play::Update()
{
	////HPが0になったらエンドシーンに移行
	//if (playerHealth_->GetHP() == 0) {
	//	SceneManager* pChangeScene = (SceneManager*)FindObject("SceneManager");
	//	pChangeScene->ChangeScene(SCENE_ID_END, TID_BLACKOUT);
	//}
}

void Scene_Play::Draw()
{
}

void Scene_Play::Release()
{
}
