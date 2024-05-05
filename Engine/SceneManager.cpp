#include "sceneManager.h"

// インクルード
#include "ResourceManager/Model.h"
#include "ResourceManager/Image.h"
#include "ResourceManager/Audio.h"

// 各シーン のインクルード
#include "../Game/Scenes/Scene_Test.h"
#include "../Game/Scenes/Scene_Splash.h"

//コンストラクタ
SceneManager::SceneManager(GameObject * parent)
	: GameObject(parent, "SceneManager"),currentSceneID_(),nextSceneID_(),tmpID_()
{
}

//初期化
void SceneManager::Initialize()
{
	//最初のシーンを準備
#ifdef _DEBUG
	currentSceneID_ = SCENE_ID_TEST;
	nextSceneID_ = currentSceneID_;
	Instantiate<Scene_Test>(this);
#else
	currentSceneID_ = SCENE_ID_SPLASH;
	nextSceneID_ = currentSceneID_;
	Instantiate<SplashScene>(this);
#endif // _DEBUG

}

//更新
void SceneManager::Update()
{
	//トランジション実行時、シーン切替のタイミングでシーンを変更する
	if (Transition::IsChangePoint())nextSceneID_ = tmpID_;

	//次のシーンが現在のシーンと違う　＝　シーンを切り替えなければならない
	if (currentSceneID_ != nextSceneID_)
	{
		//そのシーンのオブジェクトを全削除
		KillAllChildren();

		//ロードしたデータを全削除
		Audio::Release();
		Model::AllRelease();
		Image::AllRelease();

		//次のシーンを作成
		switch (nextSceneID_)
		{
		case SCENE_ID_TEST: Instantiate<Scene_Test>(this); break;
		case SCENE_ID_SPLASH: Instantiate<Scene_Splash>(this); break;
		}
		Audio::Initialize();
		currentSceneID_ = nextSceneID_;
	}
}

//描画
void SceneManager::Draw()
{
}

//開放
void SceneManager::Release()
{
}

//シーン切り替え（実際に切り替わるのはこの次のフレーム）
void SceneManager::ChangeScene(SCENE_ID next, TRANSITION_ID _type, float _time)
{
	//トランジションが動作中はシーン遷移を行わない
	if (!Transition::IsActive()) {
		//トランジションを使わない場合、シーンIDをセット
		if (!Transition::SetTransition(_type))nextSceneID_ = next;

		//時間をセット
		Transition::SetTime(_time);

		//トランジションを開始し、シーンIDをセット
		Transition::Start(); tmpID_ = next;
	}
}
void SceneManager::ChangeScene(SCENE_ID next, TRANSITION_ID _type) { ChangeScene(next, _type, 2); }
void SceneManager::ChangeScene(SCENE_ID next) { ChangeScene(next, TID_NONE); }


