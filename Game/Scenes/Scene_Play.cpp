#include "Scene_Play.h"

// インクルード
#include"../Objects/Stage/SkySphere.h"
#include"../Objects/Stage/Stage.h"
#include"../Objects/Stage/Components/GaugeComponents/Component_HealthGauge.h"
#include"../Objects/Stage/Components/BehaviorComponents/Component_PlayerBehavior.h"
#include"../../Engine/SceneManager.h"
#include "../Objects/UI/UIButton.h"
#include "../Objects/Camera/TPSCamera.h"
#include "../../Engine/ImGui/imgui.h"
#include "../../Engine/Global.h"
#include "../../Engine/ResourceManager/Image.h"
#include "../Objects/UI/CountDown.h"
#include "../../Engine/DirectX/Input.h"


Scene_Play::Scene_Play(GameObject* parent)
{
}

void Scene_Play::Initialize()
{
	UIPanel* panel_ = UIPanel::GetInstance();
	//画像データのロード

	// スカイスフィアの生成
	SkySphere* skySphere = Instantiate<SkySphere>(this);

	// stageLayout_jsonファイルを読み込む
	json loadData;
	if (JsonReader::Load("Models/Player/playerBehaviorTest.json", loadData)) {

		// ステージを作成
		pStage_ = Instantiate<Stage>(this);
		pStage_->Load(loadData);
	}

	// カメラ情報の読み込み
	json camData;
	if (JsonReader::Load("Datas/CameraLayouts/TPSCamera.json", camData)) {

		tpsCamera_ = Instantiate<TPSCamera>(this);
		tpsCamera_->Load(camData);
		tpsCamera_->SetActive(false);
	}

	countDown_ = Instantiate<CountDown>(this);
}

void Scene_Play::Update()
{
	// カーソル固定化処理
	static bool fixedCursorPos = false; {

		// 固定化の切り替え
		if (Input::IsKeyDown(DIK_F3))fixedCursorPos = !fixedCursorPos;
		
		// カーソルの位置を中央に固定
		if (fixedCursorPos) {
			SetCursorPos(Direct3D::screenWidth_ / 2, Direct3D::screenHeight_ / 2);
		}
	}
	
	static bool isGameStart = false;
	if (countDown_->IsFinished() && isGameStart == false) {

		// カーソルの位置を中央に固定
		fixedCursorPos = true;
		
		// カメラのアクティブ化
		tpsCamera_->SetActive(true);

		isGameStart = true;
	}

	// シーン切替処理
	{
		bool isSceneChange = false;

		// プレイヤーが死んだらシーンを切り替える
		{
			// ステージ内にプレイヤーコンポーネントを持っているキャラクターが存在するかどうかを判定し取得
			vector<Component*> comp_playerBehaviors = pStage_->FindComponents(PlayerBehavior);

			// ステージ内にボスコンポーネントを持っているキャラクターが存在するかどうかを判定し取得
			vector<Component*> comp_bossBehaviors = pStage_->FindComponents(BossBehavior);


			// 範囲for文でプレイヤーコンポーネントの生存フラグを確認
			for (auto comp : comp_playerBehaviors) {

				auto healthGauge = comp->GetChildComponent(ComponentType::HealthGauge);

				for (auto hg : healthGauge) {
					if (((Component_HealthGauge*)hg)->IsDead()) {
						// シーンを切り替える
						SceneManager* sceneManager = (SceneManager*)FindObject("SceneManager");
						sceneManager->ChangeScene(SCENE_ID_END, TID_BLACKOUT);
					}
				}
			}

			// 範囲for文でプレイヤーコンポーネントの生存フラグを確認
			for (auto comp : comp_bossBehaviors) {

				auto healthGauge = comp->GetChildComponent(ComponentType::HealthGauge);

				for (auto hg : healthGauge) {
					if (((Component_HealthGauge*)hg)->IsDead()) {
						// シーンを切り替える
						SceneManager* sceneManager = (SceneManager*)FindObject("SceneManager");
						sceneManager->ChangeScene(SCENE_ID_END, TID_BLACKOUT);
					}
				}
			}
		}
		//// debug
		//{
		//	if (ImGui::Button("end")) {
		//		g_score = 100;
		//		isSceneChange = true;
		//	}
		//}

		//// シーン切替処理
		//if (isSceneChange) {
		//	// シーンを切り替える
		//	SceneManager* sceneManager = (SceneManager*)FindObject("SceneManager");
		//	sceneManager->ChangeScene(SCENE_ID_END, TID_BLACKOUT);
		//}
	}

}

void Scene_Play::Draw()
{
}
void Scene_Play::Release()
{
}
