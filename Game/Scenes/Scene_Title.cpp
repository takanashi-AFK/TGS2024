#include "Scene_Title.h"

// インクルード
#include"../../Engine/SceneManager.h"
#include "../../Engine/DirectX/Input.h"
#include "../Objects/UI/UIPanel.h"
#include "../Objects/UI/UIButton.h"
#include"../../Engine/ResourceManager/Audio.h"


Scene_Title::Scene_Title(GameObject* parent)
	: GameObject(parent, "Scene_Title"), bgmHandle_(-1), seHandle_(-1)
{
}

void Scene_Title::Initialize()
{
	////// UIパネルの生成
	//pUIPanel_ = Instantiate<UIPanel>(this); {
	//	json uiData;
	//	if(JsonReader::Load("Datas/UILayouts/TitleScene.json", uiData))pUIPanel_->Load(uiData);
	//}

	////UIPanelの作成
	//pUIPanel_ = (UIPanel*)CreateUIObject(objectName_, UI_NONE, nullptr, 0); {
	//	json uiData;
	//	if (JsonReader::Load("Datas/UILayouts/TitleScene.json", uiData))pUIPanel_->Load(uiData);
	//}

	bgmHandle_ = Audio::Load("Audio\\TestBGM.wav", true);
	assert(bgmHandle_ >= 0);

	seHandle_ = Audio::Load("Audio\\TestSE.wav");
	assert(seHandle_ >= 0);
}

void Scene_Title::Update()
{
	Audio::Play(bgmHandle_);

	//// ボタンが押されたらプレイシーンに移行
	//UIButton* button = (UIButton*)pUIPanel_->GetUIObject("02StartButton");
	//if (button == nullptr)return;
	//if (button->OnClick()) {
	//	SceneManager* pChangeScene = (SceneManager*)FindObject("SceneManager");
	//	pChangeScene->ChangeScene(SCENE_ID_PLAY, TID_BLACKOUT);
	//}
}

void Scene_Title::Draw()
{
}

void Scene_Title::Release()
{
}
