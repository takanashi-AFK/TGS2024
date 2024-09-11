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
	json loadData;

	// スカイスフィアの生成
	SkySphere* skySphere = Instantiate<SkySphere>(this);

	if (JsonReader::Load("Datas/UILayouts/ResultScene_layout.json", loadData)) {

		// UIパネルを取得
		panel = UIPanel::GetInstance();
		panel->Load(loadData);
		UIText* scoreNum = (UIText*)panel->GetUIObject("ScoreNum");

		scoreNum->SetText(&ScoreManager::g_Score);

		UIText* timeNum = (UIText*)panel->GetUIObject("TimeNum");

		// timeNum->SetText(&ScoreManager::g_Time);

		UIText* hpNum = (UIText*)panel->GetUIObject("HPNum");

		// hpNum->SetText(&ScoreManager::g_HP);

	}

	// ステージを作成
	Stage* pStage = Instantiate<Stage>(this); {
		json stageData;
		JsonReader::Load("Datas/StageLayouts/EndSceneStage.json", stageData);
		pStage->Load(stageData);
	}
}

void Scene_Result::Update()
{
	UIButton* button = (UIButton*)panel->GetUIObject("NextSceneButton");

	// ボタンが押されたら
	if (button->OnClick()) {
		SceneManager* sceneManager = (SceneManager*)FindObject("SceneManager");
		sceneManager->ChangeScene(SCENE_ID_END, TID_BLACKOUT);
	}

	
	// カメラの位置と注視点を取得
	XMFLOAT3 camPos = Camera::GetPosition();
	XMFLOAT3 camTarget = Camera::GetTarget();
	// カメラの高さを固定
	camPos.y = CAMERA_HEIGHT;

	// 1fにつき回転する角度
	static float angle = 0.01f;

	// 回転行列を作成 (Y軸周りに回転)
	XMMATRIX rotationMatrix = XMMatrixRotationY(angle);

	// カメラの位置をベクトル化
	XMVECTOR vCamPosition = XMLoadFloat3(&camPos);

	// カメラの位置を座標回転
	vCamPosition = XMVector3Transform(vCamPosition, rotationMatrix);
	XMStoreFloat3(&camPos, vCamPosition);

	// カメラの位置と注視点を設定
	Camera::SetPosition(camPos);
	Camera::SetTarget(0,0,0);
}

void Scene_Result::Draw()
{
}

void Scene_Result::Release()
{
}
