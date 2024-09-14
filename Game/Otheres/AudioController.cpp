#include "AudioController.h"

// インクルード
#include "../../Engine/ResourceManager/Audio.h"
#include "../../Engine/SceneManager.h"
#include "../../Game/Objects/UI/UIPanel.h"
#include "../Objects/UI/UIButton.h"


void AudioController::Update(GameObject* _root)
{
	// 条件を未術し、満たした時に音楽を再生したり、停止したりする処理を記述

	// UIパネルを取得
	UIPanel* uiPanel = UIPanel::GetInstance();

	// シーンに依存したオーディオの再生/停止処理
	{
		// シーンマネージャーを取得
		SceneManager* sm = (SceneManager*)_root->FindObject("SceneManager");

		if(sm->IsCurrentScene(SCENE_ID_TITLE))
		{
			// タイトルシーンの場合
			// タイトルBGMを再生
			Audio::Play(Audio::Load("Audios/Retro-Beat.wav",true));

			// ボタンが押されたときのSEを再生
			{
				// ボタンを取得
				UIButton* button = (UIButton*)uiPanel->GetUIObject("title_startButton");
				
				// ボタンが押されたか
				if(button!= nullptr)if(button->OnClick()){
					Audio::Play(Audio::Load("Audios/決定ボタンを押す2.wav",false));
				}
			}
		}

		else
		{
			// タイトルシーン以外の場合
			// タイトルBGMを停止
			Audio::Stop(Audio::Load("Audios/Retro-Beat.wav",true));
		}

	}

}
