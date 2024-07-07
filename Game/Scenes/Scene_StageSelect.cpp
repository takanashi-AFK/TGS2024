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
	if (JsonReader::Load("Datas/UILayouts/StageSelect.json", uiData)) {
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
	maxButtonmove_ = 1.5f;
	
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
		isSelectButtonMoving_ = true;
		
		StageIndex = (StageIndex + 1) % stageImages.size();
	}
	
	//Buttonが押されたら-方向に移動し画像を入れ替える
	UIButton* buckButton = dynamic_cast<UIButton*>(uipanel->GetUIObject("BuckButton"));
	if (buckButton == nullptr)return;
	if (buckButton->OnClick()) {
		//isSelectButtonMovingをtrueにする
		isSelectButtonMoving_ = true;

		StageIndex = (StageIndex - 1 + stageImages.size()) % stageImages.size();
	}

	if (isSelectButtonMoving_) {
		

		for (int i = 0; i < stageImages.size(); ++i) {
			
			UIButton* button = stageImages[i];

			//そのi番目にあるボタンの画像のx座標をを取得し変数名に代入
			float ButtonPos = button->GetPosition().x;

			moveselectButton += 0.01;

			button->SetPosition(ButtonPos += moveselectButton , stageImages[i]->GetPosition().y, stageImages[i]->GetPosition().z);
			
		}
		
		//moveselevvutButtonがmaxButtonmove分移動したら
		if (moveselectButton >= maxButtonmove_) {
			moveselectButton = 0;
			isSelectButtonMoving_ = false;
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
