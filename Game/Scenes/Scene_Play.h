#pragma once

// インクルード
#include"../../Engine/GameObject/GameObject.h"
#include "../Objects/UI/UIPanel.h"
#include "../Objects/UI/UIImage.h"

// 前方宣言
class Stage;
class CountDown;
class TPSCamera;
class StageObject;
class Component;
class Scene_Play:public GameObject
{
private:
	Stage* pStage_;

	CountDown* countDown_;
	TPSCamera* tpsCamera_;
	StageObject* player_;

	Component* phm;
	Component* bhm;
public:
	//コンストラクタ
	Scene_Play(GameObject* parent);

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;
};

