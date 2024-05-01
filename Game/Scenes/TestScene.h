#pragma once
#include "../../Engine/GameObject/GameObject.h"

class Stage;

//テストシーンを管理するクラス
class TestScene : public GameObject
{
	Stage* pStage_;
public:
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	TestScene(GameObject* parent);

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;
};