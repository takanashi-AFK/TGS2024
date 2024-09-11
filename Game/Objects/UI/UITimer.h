#pragma once
#include "UIObject.h"

class UITimer : public UIObject
{
private:
	float count_;	// 現在値
	float max_;		// 最大値

	bool isActive_;	// タイマーが動いているか
public:
	/// <summary> コンストラクタ </summary>
	UITimer(string _name, UIObject* parent, int _layerNum);

	/// <summary> 初期化 </summary>
	void Initialize() override;

	/// <summary> 更新 </summary>
	void Update() override;

	/// <summary> 描画 </summary>
	void Draw() override;

	/// <summary> 解放 </summary>
	void Release() override;

	/// <summary> 保存 </summary>
	void Save(json& saveObj) override;

	/// <summary> 読込 </summary>
	void Load(json& loadObj) override;

	/// <summary> ImGui表示 </summary>
	void DrawData() override;

	/// <summary> タイマーの開始 </summary>
	void StartTimer() { isActive_ = true; }

	/// <summary> タイマーの停止 </summary>
	void StopTimer() { isActive_ = false; }

	/// <summary> タイマーの終了 </summary>
	void EndTimer() { count_ = 0; isActive_ = false; }

/*
setter :*/
	/// <summary> タイマーの設定 </summary>
	void SetTimer(float _max) { max_ = _max; count_ = max_; }

	/// <summary> タイマーのリセット </summary>
	void ResetTimer() { count_ = max_; isActive_ = false; }
/*
getter :*/
	/// <summary> タイマーの取得 </summary>
	float GetTimer() const { return count_; }

	/// <summary> 最大値の取得 </summary>
	float GetMaxTimer() const { return max_; }

/*
predicate :*/
	/// <summary> タイマーが0になったか </summary>
	bool IsEnd() const { return count_ <= 0; }

	/// <summary> タイマーが最大値か </summary>
	bool IsMax() const { return count_ >= max_; }
};

