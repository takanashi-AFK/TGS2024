#pragma once
#include"../../Engine/GameObject/GameObject.h"

class Scene_Play:public GameObject
{

	
public:

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

