#pragma once
#include "../../../../Engine/GameObject/GameObject.h"

// インクルード
#include<vector>

class CountDown : public GameObject
{
private:
	std::vector<int> countDownImages_;	// カウントダウン画像
	float count_;						// 経過時間

	bool isActive_;						// カウントダウンが有効か
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

	/// <summary> カウントダウンの開始 </summary>
	void Start() { isActive_ = true; }

/*
getter :*/
	/// <summary> カウントダウンの現在の時間を取得 </summary>
	float GetCount() const;

	/// <summary> カウントダウンが有効か </summary>
	bool IsActive() const { return isActive_; }
/*
predicate :*/
	/// <summary> カウントダウンが終了したか </summary>
	bool IsFinished() const { return count_ <= 0; }
};
