#include "Scene_StageSelect.h"

//インクルード
#include "../../Engine/Global.h"
#include "../Objects/UI/UIPanel.h"
#include "../Objects/UI/UIButton.h"
#include "../../Engine/ImGui/imgui.h"
#include "../../Engine/DirectX/Input.h"

namespace fs = std::filesystem;

namespace {
	const float DISTANCE = 1.5f;
	const float SCALE = 0.6f;
	const string EASE_FUNC = "InOutQuart";

}

Scene_StageSelect::Scene_StageSelect(GameObject* parent)
	: GameObject(parent, "Scene_StageSelect")
{
}

void Scene_StageSelect::Initialize()
{
	// UIパネルの生成
	pUIPanel_ = Instantiate<UIPanel>(this); {
		json uiData;
		if (JsonReader::Load("Datas/UILayouts/StageSelectScene.json", uiData))pUIPanel_->Load(uiData);
	}

	// ボタンの生成
	{
		// "Datas/StageLayouts"フォルダ内のjsonファイルを取得
		std::string path = "Datas/StageLayout";
		std::vector<fs::path> json_files;

		for (const auto& entry : fs::directory_iterator(path)) {
			if (entry.path().extension() == ".json") {
				json_files.push_back(entry.path());
			}
		}

		float x = 0;
		for (auto json_file : json_files) {

			// ボタンの生成
			string stageName = json_file.stem().filename().string();
			UIButton* button = (UIButton*)CreateUIObject(stageName, UI_BUTTON, pUIPanel_); {
				button->SetImage( "Images/Stages/" + stageName + ".png");
				button->SetPositionX(x);
				button->SetScale(SCALE);
			}
			x += DISTANCE;

			// ボタンをUIパネルに追加
			pUIPanel_->AddUIObject(button);
		}
	}
}

void Scene_StageSelect::Update()
{

	if (Input::IsKeyDown(DIK_D) && pUIPanel_->GetUIObjects().size()) {
		for (auto button : pUIPanel_->GetUIObjects()) {
			if (((UIButton*)button)->IsMove() == false) ((UIButton*)button)->Move(DISTANCE,{ 1,0,0,0 }, EASE_FUNC);
		}
	}

	
	if (Input::IsKeyDown(DIK_A) && selectIndex_ > selectIndex_ <= 0) {
		for (auto button : pUIPanel_->GetUIObjects()) {
			if (((UIButton*)button)->IsMove() == false) ((UIButton*)button)->Move(DISTANCE, { -1,0,0,0 }, EASE_FUNC);
		}
	}
}

void Scene_StageSelect::Draw()
{
}

void Scene_StageSelect::Release()
{
}
