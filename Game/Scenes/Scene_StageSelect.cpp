#include "Scene_StageSelect.h"

//インクルード
#include"../../Engine/SceneManager.h"
#include "../../Engine/DirectX/Input.h"
#include "../Objects/UI/UIPanel.h"
#include "../Objects/UI/UIButton.h"
Scene_StageSelect::Scene_StageSelect(GameObject* parent)
	: GameObject(parent, "Scene_StageSelect"), isSelectButtonMoving_(false), moveselectButton(0.0f)
{
}

void Scene_StageSelect::Initialize()
{
	uipanel = Instantiate<UIPanel>(this);
	json uiData;
	if (JsonReader::Load("Datas/UILayouts/StageSelect.json", uiData)) {
		uipanel->Load(uiData);
	}

	StageIndex = 0;

	stageImages.push_back(dynamic_cast<UIButton*>(uipanel->GetUIObject("StageSelectButton1")));
	stageImages.push_back(dynamic_cast<UIButton*>(uipanel->GetUIObject("StageSelectButton2")));

	
}

void Scene_StageSelect::Update()
{
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
		moveselectButton = 5.f;
		isSelectButtonMoving_ = true;
	}

	//Buttonが押されたら-方向に移動し画像を入れ替える
	UIButton* backButton = dynamic_cast<UIButton*>(uipanel->GetUIObject("BuckButton"));
	if (backButton == nullptr)return;
	if (backButton->OnClick()) {
		isSelectButtonMoving_ = true;
		moveselectButton = -5.f;
	}
	//trueになっている間x方向にButtonが移動しある程度まで行ったらfalseにする
	if (isSelectButtonMoving_ == true) {
		//stageSelectButtonのx座標だけ取得
		float selectButtonPos = stageSelectButton->GetPosition().x;
        
		//Buttonのx座標更新
		selectButtonPos += moveselectButton;

		// 位置更新
		stageSelectButton->SetPosition({ selectButtonPos, stageSelectButton->GetPosition().y,stageSelectButton->GetPosition().z});

	}

}

void Scene_StageSelect::Draw()
{
}

void Scene_StageSelect::Release()
{
}
