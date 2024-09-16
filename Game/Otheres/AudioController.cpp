#include "AudioController.h"

// インクルード
#include "../../Engine/ResourceManager/Audio.h"
#include "../../Engine/SceneManager.h"
#include "../../Game/Objects/UI/UIPanel.h"
#include "../Objects/UI/UIButton.h"
#include "../Objects/UI/CountDown.h"
#include "../Objects/Stage/Stage.h"
#include "../Objects/Stage/Components/GaugeComponents/Component_HealthGauge.h"

namespace {
	const string TITLE_BGM = "Audios/プレゼントコーナー.wav";
	const string PLAY_BGM = "Audios/Fried_Chicken_Scramble.wav";
	const string BUTTON_SE = "Audios/決定ボタンを押す2.wav";

	const string COUNTDOWN_SE = "Audios/Countdown03-2.wav";
	const string DAMAGE_SE = "Audios/打撃1.wav";
	const string DODGE_SE = "Audios/きらーん2.wav";
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
		if (countDown->IsActive())Audio::Play(Audio::Load(COUNTDOWN_SE, false));

		// ステージを取得
		Stage* stage = (Stage*)_root->FindObject("Stage");

		// ダメージを受けた時の音の再生
		for (auto hg : stage->FindComponents(HealthGauge)) {
			if (((Component_HealthGauge*)hg)->IsUnlockAndReduce()) Audio::Play(Audio::Load(DAMAGE_SE, false));
			if (((Component_HealthGauge*)hg)->IsLockAndReduce()) Audio::Play(Audio::Load(DODGE_SE, false));
		}
	}
	else
	{
		// タイトルシーン以外のシーンであれば、タイトルBGMを再生
		if(!sceneManager->IsCurrentScene(SCENE_ID_SPLASH) && !sceneManager->IsCurrentScene(SCENE_ID_END))Audio::Play(Audio::Load(TITLE_BGM, true));
		Audio::Stop(Audio::Load(PLAY_BGM, true));
	}
}
