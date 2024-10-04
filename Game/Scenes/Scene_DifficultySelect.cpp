#include "Scene_DifficultySelect.h"
#include "../Objects/UI/UIPanel.h"
#include "../Constants.h"
#include "../Objects/UI/UIButton.h"
#include "../../Engine/Global.h"
#include "../../Engine/SceneManager.h"
#include "../../Engine/DirectX/Input.h"

using namespace Constants;

Scene_DifficultySelect::Scene_DifficultySelect(GameObject* parent)
	: GameObject(parent, "Scene_DifficultySelect")
{
}

void Scene_DifficultySelect::Initialize()
{
	// UIパネル & レイアウトの読み込み
	json loadData;
	if (JsonReader::Load(DIFFICULTY_SELECT_SCENE_UI_LAYOUT_JSON, loadData)) UIPanel::GetInstance()->Load(loadData);
}

void Scene_DifficultySelect::Update()
{
	bool isClicked = false;

	// 難易度を選択
	{
		UIButton* easyButton = (UIButton*)UIPanel::GetInstance()->GetUIObject(DIFFICULTY_SELECT_SCENE_EASY_BUTTON_NAME);
		if (easyButton->OnClick() == true || Input::IsPadButtonDown(XINPUT_GAMEPAD_A)) { g_selectedStage = STAGE_EASY_JSON; isClicked = true; }

		UIButton* normalButton = (UIButton*)UIPanel::GetInstance()->GetUIObject(DIFFICULTY_SELECT_SCENE_NORMAL_BUTTON_NAME);
		if (normalButton->OnClick() == true || Input::IsPadButtonDown(XINPUT_GAMEPAD_X)) { g_selectedStage = STAGE_NORMAL_JSON; isClicked = true; }

		UIButton* hardButton = (UIButton*)UIPanel::GetInstance()->GetUIObject(DIFFICULTY_SELECT_SCENE_HARD_BUTTON_NAME);
		if (hardButton->OnClick() == true || Input::IsPadButtonDown(XINPUT_GAMEPAD_Y)) { g_selectedStage = STAGE_HARD_JSON; isClicked = true; }

		UIButton* expertButton = (UIButton*)UIPanel::GetInstance()->GetUIObject(DIFFICULTY_SELECT_SCENE_EXPERT_BUTTON_NAME);
		if (expertButton->OnClick() == true || Input::IsPadButtonDown(XINPUT_GAMEPAD_B)) { g_selectedStage = ScoreManager::userName != "insane" ? STAGE_EXPERT_JSON : STAGE_INSANE_JSON; isClicked = true; }
	}

	// シーン切替処理
	if (isClicked == true) {
		SceneManager* sceneManager = (SceneManager*)FindObject("SceneManager");
		sceneManager->ChangeScene(SCENE_ID_PLAY, TID_WHITEOUT);
	}
}

void Scene_DifficultySelect::Draw()
{
}

void Scene_DifficultySelect::Release()
{
}
