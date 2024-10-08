#include "Scene_Result.h"

// インクルード
#include "../../Engine/Global.h"
#include "../../Engine/SceneManager.h"
//#include "../../Engine/GameObject/Camera.h"
#include "../Constants.h"
#include "../Objects/Stage/SkySphere.h"
#include "../Objects/Stage/Stage.h"
#include "../Objects/UI/UIButton.h"
#include "../Objects/UI/UIPanel.h"
#include "../Objects/UI/UIText.h"
#include "../Otheres/RankingManager.h"
#include "../../Engine/DirectX/Input.h"

using namespace Constants;

namespace {
	const int CAMERA_HEIGHT = 30; // カメラの高さ
}

Scene_Result::Scene_Result(GameObject* parent_)
	: GameObject(parent_, "Scene_Result"), scoreNum_(0)
{
}

void Scene_Result::Initialize()
{
	ShowCursor(true);

	// jsonファイル読込用オブジェクトを用意
	json loadData;

	// スカイスフィアの生成
	SkySphere* skySphere = Instantiate<SkySphere>(this);

	// UIパネルを取得
	UIPanel* uiPanel = UIPanel::GetInstance();

	// UIパネル情報を読み込む
	if (JsonReader::Load(RESULT_SCENE_UI_LAYOUT_JSON, loadData)) uiPanel->Load(loadData);

	// UIパネルの情報を取得・設定
	{
		// テキストにプレイヤーのHPの値を設定
		UIText* hpNumText = (UIText*)uiPanel->GetUIObject(RESULT_SCENE_HP_TEXT_NAME);
		hpNumText->SetText(&ScoreManager::playerHp);

		// テキストにタイムの値を設定
		UIText* timeNumText = (UIText*)uiPanel->GetUIObject(RESULT_SCENE_TIME_TEXT_NAME);
		timeNumText->SetText(&ScoreManager::time);

		// スコアの計算
		scoreNum_ = CalculateScore(ScoreManager::isClear, ScoreManager::time, ScoreManager::playerHp);

		// テキストにスコアの値を設定
		UIText* scoreNumText = (UIText*)uiPanel->GetUIObject(RESULT_SCENE_SCORE_TEXT_NAME);
		scoreNumText->SetText(&scoreNum_);
	}

	// ランキングにスコアを追加
	RankingManager* rm = &RankingManager::GetInstance(); {
		rm->Load(RANKING_DATA_JSON);
		rm->AddScore(ScoreManager::userName, scoreNum_);
		rm->Save(RANKING_DATA_JSON);
	}

	// ステージを作成 & 読み込み
	Stage* pStage = Instantiate<Stage>(this);
	if(JsonReader::Load(STAGE_BACKGROUND_JSON, loadData))pStage->Load(loadData);
}

void Scene_Result::Update()
{
	// シーン遷移ボタンの処理
	{
		// UIButtonの取得
		UIButton* button = (UIButton*)UIPanel::GetInstance()->GetUIObject(RESULT_SCENE_NEXT_BUTTON_NAME);

		// ボタンが押されたら
		if (button->OnClick() || Input::IsPadButtonDown(XINPUT_GAMEPAD_A)) {
			SceneManager* sceneManager = (SceneManager*)FindObject("SceneManager");
			sceneManager->ChangeScene(SCENE_ID_END, TID_BLACKOUT);
		}
	}

	// カメラの回転処理
	{
		//// カメラの位置と注視点を取得
		//XMFLOAT3 camPos = Camera::GetPosition();
		//XMFLOAT3 camTarget = Camera::GetTarget();

		//// カメラの高さを固定
		//camPos.y = CAMERA_HEIGHT;

		//// 1fにつき回転する角度
		//static float angle = 0.005f;

		//// 回転行列を作成 (Y軸周りに回転)
		//XMMATRIX rotationMatrix = XMMatrixRotationY(angle);

		//// カメラの位置をベクトル化
		//XMVECTOR vCamPosition = XMLoadFloat3(&camPos);

		//// カメラの位置を座標回転
		//vCamPosition = XMVector3Transform(vCamPosition, rotationMatrix);
		//XMStoreFloat3(&camPos, vCamPosition);

		//// カメラの位置と注視点を設定
		//Camera::SetPosition(camPos);
		//Camera::SetTarget(0, 0, 0);
	}
}

void Scene_Result::Draw()
{
}

void Scene_Result::Release()
{
}

int Scene_Result::CalculateScore(bool isCleared, int remainingTime, int remainingHP)
{
	if (!isCleared) {
		return 0; // クリアしていない場合のスコア
	}
	int clearBonus = 1000;					// クリアボーナス (1000ポイント)
	int timeBonus = remainingTime * 100;	// 時間のボーナス（1秒あたり100ポイント）
	int hpBonus = remainingHP * 500;		// HPのボーナス（HP1あたり500ポイント）

	return clearBonus + timeBonus + hpBonus;
}
