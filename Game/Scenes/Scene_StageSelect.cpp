#include "Scene_StageSelect.h"

//インクルード
#include"../../Engine/SceneManager.h"
#include "../../Engine/DirectX/Input.h"
#include "../Objects/UI/UIPanel.h"
#include "../Objects/UI/UIButton.h"
#include"../../Engine/ImGui/imgui.h"
#include"../../Engine/DirectX/Direct3D.h"
Scene_StageSelect::Scene_StageSelect(GameObject* parent)
	: GameObject(parent, "Scene_StageSelect"), isSelectButtonMoving_(false), moveselectButton(0.f),maxButtonmove_(0.f),StageIndex(0),easingfunc_()
{
}

void Scene_StageSelect::Initialize()
{
	//UIパネルを作成
	uipanel = Instantiate<UIPanel>(this);
	//uiDataにjsonファイルが存在したのであればuipanelに保存されている
	json uiData;
	if (JsonReader::Load("Datas/UILayouts/StageSelect2.json", uiData)) {
		uipanel->Load(uiData);
	}

	
	stageImages.push_back(dynamic_cast<UIButton*>(uipanel->GetUIObject("StageSelectButton1")));
	stageImages.push_back(dynamic_cast<UIButton*>(uipanel->GetUIObject("StageSelectButton2")));
}

void Scene_StageSelect::Update()
{
#ifdef _DEBUG
	//-------Imguiでいーじんぐ関数を選ぶことで適用されてStageのImage画像が動く-------
	if (ImGui::BeginCombo("EaseFunc", easingfunc_.c_str())) {
		for (const auto& pair : Direct3D::EaseFunc) {
			bool isSelected = (easingfunc_ == pair.first);
			if (ImGui::Selectable(pair.first.c_str(), isSelected)) {
				easingfunc_ = pair.first; // Set the selected ease function
			}
			if (isSelected) {
				ImGui::SetItemDefaultFocus(); // Ensure the selected item is focused
			}
		}
		ImGui::EndCombo();
	}

#endif // DEBUG

	//---------ステージ選択画面がスクロール式で移動するようにする-----------------------------------
	maxButtonmove_ = 3.f;
	
	//stageSelectButtonが押されたらPlayシーンに移動
	UIButton* stageSelectButton = stageImages[StageIndex];
	if (stageSelectButton == nullptr)return;
	if (stageSelectButton->OnClick()) {
		SceneManager* pChangeScene = (SceneManager*)FindObject("SceneManager");
		pChangeScene->ChangeScene(SCENE_ID_PLAY, TID_BLACKOUT);
	}

	//Buttonが押されたら次の画像に移行
	UIButton* nextButton = dynamic_cast<UIButton*>(uipanel->GetUIObject("NextButton"));
	if (nextButton == nullptr)return;
	if (nextButton->OnClick()) {
		//割合を増やす
		moveselectButton = 0.01;

		isSelectButtonMoving_ = true;
		
		StageIndex = (StageIndex + 1) % stageImages.size();
	}
	
	//Buttonが押されたら-方向に移動し画像を入れ替える
	UIButton* buckButton = dynamic_cast<UIButton*>(uipanel->GetUIObject("BuckButton"));
	if (buckButton == nullptr)return;
	if (buckButton->OnClick()) {
		//isSelectButtonMovingをtrueにする
		moveselectButton = -0.01;

		isSelectButtonMoving_ = true;
		
		StageIndex = (StageIndex - 1 + stageImages.size()) % stageImages.size();
	}

	//trueになっている間StageImageがスクロール式に動く
	if (isSelectButtonMoving_) {
		for (int i = 0; i < stageImages.size(); ++i) {
			UIButton* button = stageImages[i];

			float selectButtonPos = button->GetPosition().x;

			// ボタンのx座標更新
			selectButtonPos += maxButtonmove_ * Direct3D::EaseFunc[easingfunc_](std::abs(moveselectButton));

			// 位置更新
			button->SetPosition({ selectButtonPos, button->GetPosition().y, button->GetPosition().z });


			//指定した距離移動したらisSelectButtonMovingをfalseにする
			if ((moveselectButton > 0 && selectButtonPos >= maxButtonmove_) ||
				(moveselectButton < 0 && selectButtonPos <= -maxButtonmove_)) {
				isSelectButtonMoving_ = false;
				moveselectButton = 0;
			}

		}
	}

	/*for (size_t i = 0; i < stageImages.size(); ++i)
	{
		UIButton* button = stageImages[i];
		if (button != nullptr)
		{
			ImGui::Text("Button %zu Pos: %.2f", i, button->GetPosition().x);
		}
	}*/
	
}


void Scene_StageSelect::Draw()
{
}

void Scene_StageSelect::Release()
{
}
