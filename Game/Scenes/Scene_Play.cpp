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
#include "../Objects/Stage/Components/BehaviorComponents/Component_BossBehavior.h"


Scene_Play::Scene_Play(GameObject* parent)
{
}

void Scene_Play::Initialize()
{
	UIPanel* panel_ = UIPanel::GetInstance();
	json panelData;
	if (JsonReader::Load("test_playerHPBar.json", panelData)) {
		panel_->Load(panelData);
	}

	// スカイスフィアの生成
	SkySphere* skySphere = Instantiate<SkySphere>(this);

	// stageLayout_jsonファイルを読み込む
	json loadData;
	if (JsonReader::Load("Stage01.json", loadData)) {

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
	TPSCamera* tpsCamera_ = (TPSCamera*)FindObject("TPSCamera");
	if (tpsCamera_ == nullptr)return;


	// カーソル固定化処理
	static bool fixedCursorPos = false; {

		// 固定化の切り替え
		if (Input::IsKeyDown(DIK_F3))fixedCursorPos = !fixedCursorPos;
		
		// カーソルの位置を中央に固定
		if (fixedCursorPos) {
			SetCursorPos(Direct3D::screenWidth_ / 2, Direct3D::screenHeight_ / 2);
		}
	}
	
	if (countDown_->IsFinished() && isGameStart_ == false) {

		// カーソルの位置を中央に固定
		fixedCursorPos = true;
		
		// カメラのアクティブ化
		tpsCamera_->SetActive(true);

		// ゲーム開始フラグを立てる
		isGameStart_ = true;
	}


	// シーン切替処理
	{
		// シーン切替フラグを用意
		bool isSceneChange = false;
		
		// プレイヤーが死んだ場合、切替フラグを立てる
		for (auto playerBehavior : pStage_->FindComponents(ComponentType::PlayerBehavior))if (((Component_PlayerBehavior*)playerBehavior)->IsDead()) isSceneChange = true;
		
		// ボスが死んだ場合、切替フラグを立てる
		 for (auto bossBehavior : pStage_->FindComponents(ComponentType::BossBehavior)) if(((Component_BossBehavior*)bossBehavior)->IsDead()) isSceneChange = true;

		// シーン切替フラグが立っている場合
		if (isSceneChange == true) {

			// シーンを切り替える
			SceneManager* sceneManager = (SceneManager*)FindObject("SceneManager");
			sceneManager->ChangeScene(SCENE_ID_RESULT, TID_BLACKOUT);
		}
	}

	// カメラの更新
	{
		// プレイヤーをカメラのターゲットに設定
		for (auto playerBehavior : pStage_->FindComponents(ComponentType::PlayerBehavior))tpsCamera_->SetTarget(playerBehavior->GetHolder());
	}
}

void Scene_Play::Draw()
{
}
void Scene_Play::Release()
{
}

// あとボスが死んだ際のシーン切り替えできてないから確認する
// 処理順をプレイヤーと入れ替えるとかなんかそんな感じで