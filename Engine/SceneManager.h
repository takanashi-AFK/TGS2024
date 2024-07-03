#pragma once
#include "global.h"
#include "GameObject/GameObject.h"
#include "ResourceManager/Transition.h"

//ゲームに登場するシーン
enum SCENE_ID
{
	SCENE_ID_TEST = 0,
	SCENE_ID_SPLASH,
	SCENE_ID_TITLE,
	SCENE_ID_PLAY,
	SCENE_ID_STAGESELECT,
	SCENE_ID_END
};


//-----------------------------------------------------------
//シーン切り替えを担当するオブジェクト
//-----------------------------------------------------------
class SceneManager : public GameObject
{
public:

	//コンストラクタ
	//引数：parent	親オブジェクト（基本的にゲームマネージャー）
	SceneManager(GameObject* parent);

	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;

	//シーン切り替え（実際に切り替わるのはこの次のフレーム）
	//引数：next	次のシーンのID
	//引数：type	トランジションID
	//引数：time	時間(秒)
	void ChangeScene(SCENE_ID next, TRANSITION_ID _type, float _time);
	void ChangeScene(SCENE_ID next, TRANSITION_ID _type);
	void ChangeScene(SCENE_ID next);

private:

	SCENE_ID currentSceneID_;	//現在のシーン
	SCENE_ID nextSceneID_;		//次のシーン
	SCENE_ID tmpID_;
};