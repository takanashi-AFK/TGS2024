#include "Scene_End.h"
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

Scene_End::Scene_End(GameObject* parent_)
{
}

namespace {
	const int CAMERA_HEIGHT = 25;
}

void Scene_End::Initialize()
{
	json loadData;


	// スカイスフィアの生成
	SkySphere* skySphere = Instantiate<SkySphere>(this);

		if (JsonReader::Load("Datas/UILayouts/ResultScene_layout.json", loadData)) {

			// UIパネルを取得
			panel = UIPanel::GetInstance();
			panel->Load(loadData);
			UIText* text = (UIText*)panel->GetUIObject("ScoreNum");

			text->SetText(&ScoreManager::g_Score);

			// スプラッシュシーンのパネルlayoutを設定
		}

		// ステージを作成
		Stage* pStage = Instantiate<Stage>(this); {
			json stageData;
			JsonReader::Load("Datas/StageLayouts/EndSceneStage.json", stageData);
			pStage->Load(stageData);
		}

#ifdef _DEBUG
		// ゲームエディターの生成
		GameEditor* gameEditor = Instantiate<GameEditor>(this);



		gameEditor->SetEditStage(pStage);


		// UIパネルの生成
		UIPanel* pUIPanel_ = UIPanel::GetInstance();
		gameEditor->SetEditUIPanel(pUIPanel_);

#endif // _DEBUG
	
}

void Scene_End::Update()
{
	UIButton* button = (UIButton*)panel->GetUIObject("NextSceneButton");

	if (button->OnClick()) {
		SceneManager* sceneManager = (SceneManager*)FindObject("SceneManager");
		sceneManager->ChangeScene(SCENE_ID_TITLE, TID_BLACKOUT);
	}

	XMFLOAT3 camPos = Camera::GetPosition();
	camPos.y = CAMERA_HEIGHT;
	XMFLOAT3 camTarget = Camera::GetTarget();

	static float angle = 0.01f;
	// 回転行列を作成 (Y軸周りに回転)
	XMMATRIX rotationMatrix = XMMatrixRotationY(angle);

	XMVECTOR vCamPosition = XMLoadFloat3(&camPos);

	vCamPosition = XMVector3Transform(vCamPosition, rotationMatrix);
	XMStoreFloat3(&camPos, vCamPosition);

	Camera::SetPosition(camPos.x ,camPos.y,camPos.z);
	Camera::SetTarget(0,0,0);
}

void Scene_End::Draw()
{
}

void Scene_End::Release()
{
}
