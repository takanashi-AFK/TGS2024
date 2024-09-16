#include "AudioController.h"

// インクルード
#include "../../Engine/ResourceManager/Audio.h"
#include "../../Engine/SceneManager.h"
#include "../../Game/Objects/UI/UIPanel.h"
#include "../Objects/UI/UIButton.h"
#include "../Objects/UI/CountDown.h"

namespace {
	const string TITLE_BGM = "Audios/プレゼントコーナー.wav";
	const string PLAY_BGM = "Audios/Fried_Chicken_Scramble.wav";
	const string BUTTON_SE = "Audios/決定ボタンを押す2.wav";
	const string COUNTDOWN_SE = "Audios/Countdown03-2.wav";
}

void AudioController::Update(GameObject* _root)
{
	// 条件を未術し、満たした時に音楽を再生したり、停止したりする処理を記述

	// UIパネルを取得
	UIPanel* uiPanel = UIPanel::GetInstance();

	// ボタンがクリックされた時のSE再生処理
	for (auto button : UIPanel::GetInstance()->GetUIObject(UI_BUTTON)) {
		if (((UIButton*)button)->OnClick()) Audio::Play(Audio::Load(BUTTON_SE, false));
	}

	// シーン切り替え時のBGM再生処理
	SceneManager* sceneManager = (SceneManager*)_root->FindObject("SceneManager");


	if (sceneManager->IsCurrentScene(SCENE_ID_PLAY)) {

		// 背景音楽の再生
		Audio::Play(Audio::Load(PLAY_BGM, true));
		Audio::Stop(Audio::Load(TITLE_BGM, true));

		// カウントダウンの音の再生
		CountDown* countDown = (CountDown*)_root->FindObject("CountDown");
		if(countDown->IsActive())Audio::Play(Audio::Load(COUNTDOWN_SE, false));
	}
	else
	{
		if(!sceneManager->IsCurrentScene(SCENE_ID_SPLASH) && !sceneManager->IsCurrentScene(SCENE_ID_END))Audio::Play(Audio::Load(TITLE_BGM, true));
		Audio::Stop(Audio::Load(PLAY_BGM, true));
	}
}
