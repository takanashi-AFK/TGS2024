#include "Scene_Title.h"

// インクルード
#include"../../Engine/SceneManager.h"
#include "../../Engine/DirectX/Input.h"
#include "../../Engine/ImGui/imgui.h"
#include "../Objects/UI/UIPanel.h"
#include "../Objects/UI/UIButton.h"

Scene_Title::Scene_Title(GameObject* parent)
	: GameObject(parent, "Scene_Title")
{
}

void Scene_Title::Initialize()
{
	// jsonファイルを読み込む
	json loadData;
	if (JsonReader::Load("Datas/UILayouts/titleScene_layout.json", loadData)) {

		// UIパネルを取得
		UIPanel* panel = UIPanel::GetInstance();

		// スプラッシュシーンのパネルlayoutを設定
		panel->Load(loadData);
	}
}
//
void Scene_Title::Update()
{
	// シーン切替処理
	{
		// ボタンを取得
		UIButton* button = (UIButton*)UIPanel::GetInstance()->GetUIObject("startButton");

		// ボタンが取得できたら
		if (button != nullptr) {

			// ボタンが押されたらシーンを切り替える
			if (button->OnClick() == true) {

				// シーンを切り替える
				SceneManager* sceneManager = (SceneManager*)FindObject("SceneManager");
				sceneManager->ChangeScene(SCENE_ID_PLAY, TID_BLACKOUT);
			}
		}
	}

	// debug
	ImGui::Text("Scene_Title");
}

void Scene_Title::Draw()
{
}

void Scene_Title::Release()
{
}
