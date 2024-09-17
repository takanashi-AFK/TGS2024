#pragma once

// インクルード
#include "../../Engine/GameObject/GameObject.h"

class Scene_Splash : public GameObject
{
private:
	float count_;		// 経過時間

public:
	/// <summary> コンストラクタ </summary>
	Scene_Splash(GameObject* _parent);

	/// <summary> 初期化 </summary>
	void Initialize() override;

	/// <summary> 更新 </summary>
	void Update() override;

	/// <summary> 描画 </summary>
	void Draw() override;

	/// <summary> 解放 </summary>
	void Release() override;
};

