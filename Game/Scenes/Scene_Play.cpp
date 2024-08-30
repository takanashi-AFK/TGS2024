#include "Scene_Play.h"

// インクルード
#include"../Objects/Stage/SkySphere.h"
#include"../Objects/Stage/Stage.h"
#include "../Objects/UI/UIPanel.h"
#include "../Objects/UI/UIImage.h"
#include"../Objects/Stage/Components/GaugeComponents/Component_HealthGauge.h"
#include"../Objects/Stage/Components/BehaviorComponents/Component_PlayerBehavior.h"
#include"../../Engine/SceneManager.h"
#include "../Objects/UI/UIButton.h"
#include "../Objects/Camera/TPSCamera.h"
#include "../../Engine/ImGui/imgui.h"
#include "../../Engine/Global.h"

Scene_Play::Scene_Play(GameObject* parent)
{
}

void Scene_Play::Initialize()
{
	// UIパネルを取得
	UIPanel* panel = UIPanel::GetInstance();
	for (int i = 0; i < 4; i++) {
		UIImage* countImage = (UIImage*)CreateUIObject("countDown" + std::to_string(i), UI_IMAGE, panel, i + 1);
		countImage->SetImage("ここにイメージのパス" + std::to_string(i));

		panel->PushBackChild(countImage);
	}
	// スカイスフィアの生成
	SkySphere* skySphere = Instantiate<SkySphere>(this);

	// stageLayout_jsonファイルを読み込む
	json loadData;
	if (JsonReader::Load("Datas/StageLayouts/stage01_layout.json", loadData)) {

		// ステージを作成
		pStage_ = Instantiate<Stage>(this);
		pStage_->Load(loadData);
	}

	// カメラ情報の読み込み
	json camData;
	if (JsonReader::Load("Datas/CameraLayouts/TPSCamera.json", camData)) {

		TPSCamera* tpsCamera = Instantiate<TPSCamera>(this);
		tpsCamera->Load(camData);
	}
}

void Scene_Play::Update()
{
	// シーン切替処理
	{
		bool isSceneChange = false;

		// プレイヤーが死んだらシーンを切り替える
		{
			// ステージ内にプレイヤーコンポーネントを持っているキャラクターが存在するかどうかを判定し取得
			vector<Component*> comp_playerBehaviors = pStage_->FindComponents(PlayerBehavior);

			// 範囲for文でプレイヤーコンポーネントの生存フラグを確認
			for (auto comp : comp_playerBehaviors) {

				// プレイヤーコンポーネントが死んでいたら
				if (((Component_PlayerBehavior*)comp)->IsDead() == true) {

					g_score = 0;
					isSceneChange = true;
				}
			}
		}

		// ボスが死んだらシーンを切り替える
		{
			//// ステージ内にボスコンポーネントを持っているキャラクターが存在するかどうかを判定し取得
			//vector<Component*> comp_bossBehaviors = pStage_->FindComponents(BossBehavior);

			//// 範囲for文でボスコンポーネントの生存フラグを確認
			//for (auto comp : comp_bossBehaviors) {

			//	// ボスコンポーネントが死んでいたら
			//	if (((Component_BossBehavior*)comp)->IsDead() == true) {
			//		// シーンを切り替える
			//		SceneManager* sceneManager = (SceneManager*)FindObject("SceneManager");
			//		sceneManager->ChangeScene(SCENE_ID_END, TID_BLACKOUT);
			//	}
			//}
		}

		// debug
		{
			if (ImGui::Button("end")) {
				g_score = 100;
				isSceneChange = true;
			}
		}

		// シーン切替処理
		if (isSceneChange) {
			// シーンを切り替える
			SceneManager* sceneManager = (SceneManager*)FindObject("SceneManager");
			sceneManager->ChangeScene(SCENE_ID_END, TID_BLACKOUT);
		}
	}
}

void Scene_Play::Draw()
{
}

void Scene_Play::Release()
{
}
