#include "Scene_Play.h"

// インクルード
#include"../Objects/Stage/SkySphere.h"
#include"../Objects/Stage/Stage.h"
#include "../Objects/UI/UIPanel.h"
#include"../Objects/Stage/Components/GaugeComponents/Component_HealthGauge.h"
#include"../Objects/Stage/Components/BehaviorComponents/Component_PlayerBehavior.h"
#include"../../Engine/SceneManager.h"
#include "../Objects/UI/UIButton.h"
#include "../Objects/Camera/TPSCamera.h"
#include "../../Engine/ImGui/imgui.h"

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
		JsonReader::Load("Datas/StageLayouts/stage_beta_00.json", stageData);
		pStage->Load(stageData);

		// プレイヤーとボスのヘルスゲージを取得
		for (auto pList : pStage->GetStageObjects()) {
			if (pList->FindComponent("PlayerBehavior")) {
				Component_PlayerBehavior* playerBeha = dynamic_cast<Component_PlayerBehavior*>(pList->FindComponent("PlayerBehavior"));
				if (playerBeha != nullptr) {
					playerHealth_ = dynamic_cast<Component_HealthGauge*>(playerBeha->GetChildComponent("HealthGauge"));
				}
			}
			if (pList->FindComponent("BossBehavior")) {  // ボスのコンポーネントを仮定
				Component_PlayerBehavior* bossBeha = dynamic_cast<Component_PlayerBehavior*>(pList->FindComponent("BossBehavior"));
				if (bossBeha != nullptr) {
					bossHealth_ = dynamic_cast<Component_HealthGauge*>(bossBeha->GetChildComponent("HealthGauge"));
				}
			}
		}
	}
		////範囲for分でオブジェクトリストの取得
		//for (auto pList : pStage->GetStageObjects()) {
		//	//リスト内でとうろくされているPlayerBehaviorがあったらコンポーネントをキャストして代入
		//	if (pList->FindComponent("PlayerBehavior")) {
		//		Component_PlayerBehavior* playerBeha = dynamic_cast<Component_PlayerBehavior*>(pList->FindComponent("PlayerBehavior"));
		//		if (playerBeha != nullptr) {
		//			//playerBehaから子コンポーネントを取得する
		//			playerHealth_ = dynamic_cast<Component_HealthGauge*>(playerBeha->GetChildComponent("HealthGauge"));
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

	/*if(ImGui::Button("END")) {
		SceneManager* pChangeScene = (SceneManager*)FindObject("SceneManager");
		pChangeScene->ChangeScene(SCENE_ID_END, TID_BLACKOUT);
	}*/

	//HPが0になったらエンドシーンに移行
	/*if (playerHealth_->GetHP() == 0) {
		SceneManager* pChangeScene = (SceneManager*)FindObject("SceneManager");
		pChangeScene->ChangeScene(SCENE_ID_END, TID_BLACKOUT);
	}*/
	// プレイヤーとボスのHPチェック
	/*if (playerHealth_ && playerHealth_->GetMax() <= 0)
	{
		ChangeState(LOSE);
	}
	else if (bossHealth_ && bossHealth_->GetMax() <= 0)
	{
		ChangeState(WIN);
	}*/

}

void Scene_Play::Draw()
{
}

void Scene_Play::Release()
{
}

//void Scene_Play::ChangeState(ENDSTATE newState)
//{
//	SceneManager* pChangeScene = static_cast<SceneManager*>(FindObject("SceneManager"));
//	if (pChangeScene)
//	{
//		pChangeScene->ChangeSceneState(SCENE_ID_END, newState);
//	}
//}
