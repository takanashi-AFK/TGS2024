#pragma once

// インクルード
#include"../../Engine/GameObject/GameObject.h"

// 前方宣言
class Component_HealthManager;

class Scene_Play:public GameObject
{
private:
	Component_HealthManager* playerHealth_; //プレイヤーのHPを管理するコンポーネント

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

