#include "AudioController.h"

// インクルード
#include "../../Engine/ResourceManager/Audio.h"
#include "../../Engine/SceneManager.h"

void AudioController::Update(GameObject* _root)
{
	// 条件を未術し、満たした時に音楽を再生したり、停止したりする処理を記述

	// シーンに依存したオーディオの再生/停止処理
	{
		// シーンマネージャーを取得
		SceneManager* sm = (SceneManager*)_root->FindObject("SceneManager");

		if(sm->IsCurrentScene(SCENE_ID_TITLE))
		{
			// タイトルシーンの場合
			// タイトルBGMを再生
			Audio::Play(Audio::Load("Audios/Retro-Beat.wav",true));
		}
		else
		{
			// タイトルシーン以外の場合
			// タイトルBGMを停止
			Audio::Stop(Audio::Load("Audios/Retro-Beat.wav",true));
		}

	}

}
