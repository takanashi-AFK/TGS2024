#include "Scene_Result.h"
#include "../Objects/UI/UIPanel.h"
#include "../../Engine/Global.h"
#include "../../Engine/ImGui/imgui.h"
#include "../Objects/UI/UIPanel.h"
#include "../Objects/UI/UIObject.h"
#include "../Objects/UI/UIText.h"
#include "../Objects/UI/UIButton.h"
#include "../../Engine/SceneManager.h"
#include "../Objects/Stage/Stage.h"
#include "../Objects/Camera/TPSCamera.h"
#include "../Otheres/GameEditor.h"
#include "../Objects/Stage/SkySphere.h"
#include "../../Engine/GameObject/Camera.h"

Scene_Result::Scene_Result(GameObject* parent_)
{
}

namespace {
	const int CAMERA_HEIGHT = 30;
}

void Scene_Result::Initialize()
{
	// jsonファイル読込用オブジェクトを用意
	json loadData;

	// スカイスフィアの生成
	SkySphere* skySphere = Instantiate<SkySphere>(this);

	// UIパネルを取得
	UIPanel* uiPanel = UIPanel::GetInstance();

	// UIパネル情報を読み込む
	if (JsonReader::Load("Datas/UILayouts/ResultScene_layout.json", loadData)) uiPanel->Load(loadData);

	// UIパネルの情報を取得・設定
	{
		// テキストにプレイヤーのHPの値を設定
		UIText* hpNumText = (UIText*)uiPanel->GetUIObject("HPNum");
		hpNumText->SetText(&ScoreManager::playerHp);

		// テキストにタイムの値を設定
		UIText* timeNumText = (UIText*)uiPanel->GetUIObject("TimeNum");
		timeNumText->SetText(&ScoreManager::time);

		// 上記の値値からスコアを計算
		scoreNum_ = ScoreManager::playerHp * 100 + ScoreManager::time * 10;

		// テキストにスコアの値を設定
		UIText* scoreNumText = (UIText*)uiPanel->GetUIObject("ScoreNum");
		scoreNumText->SetText(&scoreNum_);

	}

	// ステージを作成 & 読み込み
	Stage* pStage = Instantiate<Stage>(this);
	if(JsonReader::Load("Datas/StageLayouts/EndSceneStage.json", loadData))pStage->Load(loadData);
	
}

void Scene_Result::Update()
{
	// シーン遷移ボタンの処理
	{
		// UIButtonの取得
		UIButton* button = (UIButton*)UIPanel::GetInstance()->GetUIObject("NextSceneButton");

		// ボタンが押されたら
		if (button->OnClick()) {
			SceneManager* sceneManager = (SceneManager*)FindObject("SceneManager");
			sceneManager->ChangeScene(SCENE_ID_END, TID_BLACKOUT);
		}
	}

	// カメラの回転処理
	{
		// カメラの位置と注視点を取得
		XMFLOAT3 camPos = Camera::GetPosition();
		XMFLOAT3 camTarget = Camera::GetTarget();

		// カメラの高さを固定
		camPos.y = CAMERA_HEIGHT;

		// 1fにつき回転する角度
		static float angle = 0.005f;

		// 回転行列を作成 (Y軸周りに回転)
		XMMATRIX rotationMatrix = XMMatrixRotationY(angle);

		// カメラの位置をベクトル化
		XMVECTOR vCamPosition = XMLoadFloat3(&camPos);

		// カメラの位置を座標回転
		vCamPosition = XMVector3Transform(vCamPosition, rotationMatrix);
		XMStoreFloat3(&camPos, vCamPosition);

		// カメラの位置と注視点を設定
		Camera::SetPosition(camPos);
		Camera::SetTarget(0, 0, 0);
	}
}

void Scene_Result::Draw()
{
}

void Scene_Result::Release()
{
}
