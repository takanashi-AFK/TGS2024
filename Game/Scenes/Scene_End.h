#pragma once
#include"../../Engine/GameObject/GameObject.h"

enum  ENDSTATE { WIN, LOSE };
class Scene_End :public GameObject
{
private:
	

	ENDSTATE endState_;
public:
	//コンストラクタ
	Scene_End(GameObject* parent_/*, ENDSTATE state_*/);

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;

};

