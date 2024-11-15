#include "Scene_Play.h"

// インクルード
#include "../../Engine/DirectX/Input.h"
#include "../../Engine/Global.h"
#include"../../Engine/SceneManager.h"
#include "../Constants.h"
#include "../Objects/Camera/TPSCamera.h"
#include "../Objects/Stage/Components/BehaviorComponents/Component_BossBehavior.h"
#include"../Objects/Stage/Components/BehaviorComponents/Component_PlayerBehavior.h"
#include"../Objects/Stage/Components/GaugeComponents/Component_HealthGauge.h"
#include"../Objects/Stage/SkySphere.h"
#include"../Objects/Stage/Stage.h"
#include "../Objects/UI/CountDown.h"
#include "../Objects/UI/UIPanel.h"
#include "../Objects/UI/UITimer.h"


using namespace Constants;

Scene_Play::Scene_Play(GameObject* parent)
	:GameObject(parent,"Scene_Play"), pStage_(nullptr), tpsCamera_(nullptr), fixedCursorPos(true), cursorVisible(true), isGameStart_(false)
{
}

void Scene_Play::Initialize()
{
	// UIパネルの初期化
	InitUIPanel();

	// ステージの初期化
	InitStage();

	// カメラの初期化
	InitCamera();

	// カウントダウンの生成
	countDown_ = Instantiate<CountDown>(this);
	countDown_->Start();

	// カーソルの非表示化
	ShowCursor(false);
}

void Scene_Play::Update()
{
	// タイマーの取得
	UITimer* uiTimer = (UITimer*)UIPanel::GetInstance()->FindObject(PLAY_SCENE_TIMER_NAME);

	// カーソル固定化処理
	SetCursorMode();

	// ゲーム開始処理
	if (countDown_->IsFinished() && isGameStart_ == false) {
		
		// カメラのアクティブ化
		tpsCamera_->SetActive(true);

		// ゲーム開始フラグを立てる
		isGameStart_ = true;

		// タイマーの開始
		if (uiTimer != nullptr) uiTimer->StartTimer();
	}

	// シーン切替処理
	{
		// シーン切替フラグを用意
		bool isSceneChange = false;

		// プレイヤーが死んだ場合、切替フラグを立てる
		for (auto playerBehavior : pStage_->FindComponents(ComponentType::PlayerBehavior))if (((Component_PlayerBehavior*)playerBehavior)->IsDead()) {ScoreManager::isClear = false; isSceneChange = true;}
		
		// ボスが死んだ場合、切替フラグを立てる
		for (auto bossBehavior : pStage_->FindComponents(ComponentType::BossBehavior)) if (((Component_BossBehavior*)bossBehavior)->IsDead()){ScoreManager::isClear = true;isSceneChange = true;}
		
		// タイマーが終了した場合、切替フラグを立てる
		if(uiTimer!=nullptr)if (uiTimer->IsEnd()) { ScoreManager::isClear = false; isSceneChange = true; }

		// シーン切替フラグが立っている場合
		if (isSceneChange == true) {
			
			// タイマーの最終値を取得
			ScoreManager::time = uiTimer->GetSeconds();
			
			// シーンを切り替える
			SceneManager* sceneManager = (SceneManager*)FindObject("SceneManager");
			sceneManager->ChangeScene(SCENE_ID_RESULT, TID_BLACKOUT);
		}
	}

	// プレイヤーをカメラのターゲットに設定
	for (auto playerBehavior : pStage_->FindComponents(ComponentType::PlayerBehavior))tpsCamera_->SetTarget(playerBehavior->GetHolder());
}

void Scene_Play::Draw()
{
}

void Scene_Play::Release()
{
}

void Scene_Play::InitUIPanel()
{
	// UIパネル & レイアウトの読み込み
	json loadData;
	if (JsonReader::Load(PLAY_SCENE_UI_LAYOUT_JSON, loadData)) UIPanel::GetInstance()->Load(loadData);
}

void Scene_Play::InitStage()
{
	// スカイスフィアの生成
	Instantiate<SkySphere>(this);

	// ステージデータの読み込み
	json loadData;
	if (JsonReader::Load(g_selectedStage, loadData)) {

		// ステージを生成
		pStage_ = Instantiate<Stage>(this);
		
		// ステージの読み込み
		pStage_->Load(loadData);
	}
}

void Scene_Play::InitCamera()
{
	// カメラ情報の読み込み
	json loadData;
	if (JsonReader::Load(PLAY_SCENE_CAMERA_LAYOUT_JSON, loadData)) {

		// カメラの生成
		tpsCamera_ = Instantiate<TPSCamera>(this);
		
		// カメラの読み込み
		tpsCamera_->Load(loadData);

		// カメラのアクティブ化
		tpsCamera_->SetActive(false);
	}
}

void Scene_Play::SetCursorMode()
{
	// F3キーが押されたら
	if (Input::IsKeyDown(DIK_F3)) {

		// カーソル固定化の切り替え
		fixedCursorPos = !fixedCursorPos;

		// カーソルの表示状態を切り替える
		cursorVisible = !fixedCursorPos;
		ShowCursor(cursorVisible);
	}

	// カーソルの位置を中央に固定
	if (fixedCursorPos) {
		SetCursorPos(Direct3D::screenWidth_ / 2, Direct3D::screenHeight_ / 2);
	}
}
