#include "Scene_StageSelect.h"

//インクルード
#include"../../Engine/SceneManager.h"
#include "../../Engine/DirectX/Input.h"
#include "../Objects/UI/UIPanel.h"
#include "../Objects/UI/UIButton.h"
Scene_StageSelect::Scene_StageSelect(GameObject* parent)
: GameObject(parent, "Scene_StageSelect")
{
}

void Scene_StageSelect::Initialize()
{
	uipanel = Instantiate<UIPanel>(this); 
	json uiData;
	if (JsonReader::Load("Datas/UILayouts/StageSelect.json", uiData)){
			uipanel->Load(uiData);
	}

	StageIndex = 0;

	stageImages.push_back(dynamic_cast<UIButton*>(uipanel->GetUIObject("StageSelectButton1")));
	stageImages.push_back(dynamic_cast<UIButton*>(uipanel->GetUIObject("StageSelectButton2")));

}

void Scene_StageSelect::Update()
{
	//Buttonが押されたら次の画像に移行
	UIButton* nextButton = dynamic_cast<UIButton*>(uipanel->GetUIObject("nextButton"));
	if (nextButton == nullptr)return;
	if (nextButton->OnClick()) {
		StageIndex = StageIndex + 1;
		transform_.position_.x = stageImages[StageIndex]->GetPosition().x;
	}
	
	//Buttonが押されたら一個前の画像に戻る
	UIButton* backButton = dynamic_cast<UIButton*>(uipanel->GetUIObject("backButton"));
	if (backButton == nullptr)return;
	if (backButton->OnClick()) {
		StageIndex = StageIndex - 1 + stageImages.size();
		transform_.position_.x = stageImages[StageIndex]->GetPosition().x;
	}

	UIButton* stageSelectButton = stageImages[StageIndex];
	if (stageSelectButton == nullptr)return;
	if (stageSelectButton->OnClick()){
		SceneManager* pChangeScene = (SceneManager*)FindObject("SceneManager");
		pChangeScene->ChangeScene(SCENE_ID_PLAY, TID_BLACKOUT);
	}


}

void Scene_StageSelect::Draw()
{
}

void Scene_StageSelect::Release()
{
}
