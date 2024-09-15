#pragma once
#include "../../../../Engine/GameObject/GameObject.h"

// インクルード
#include<vector>

class CountDown : public GameObject
{
private:
	std::vector<int> countDownImages_;	// カウントダウン画像
	float count_;						// 経過時間

public:
	/// <summary> コンストラクタ </summary>
	CountDown(GameObject* _parent);

	/// <summary> 初期化 </summary>
	void Initialize() override;

	/// <summary> 更新 </summary>
	void Update() override;

	/// <summary> 描画 </summary>
	void Draw() override;

	/// <summary> 解放 </summary>
	void Release() override;
/*
predicate :*/
	/// <summary> カウントダウンが終了したか </summary>
	bool IsFinished() const { return count_ <= 0; }
};
