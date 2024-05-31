#pragma once

// インクルード
#include "../Component.h"

/// <summary>
/// タイマーを管理するコンポーネント
/// </summary>
class Component_Timer : public Component
{
private:
	float maxTime_;		// 最大時間
	float nowTime_;		// 現在の時間
	float tempMax_;		// 一時的な最大時間
	bool isEnd_;		// 終了したか
	bool isCountNow_;	// カウント中か
	bool isInfinity_;	// 無限にカウントするか

public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="_holder">保有者</param>
	Component_Timer(string _name,StageObject* _holder, Component* _parent);

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize() override;

	/// <summary>
	/// 更新
	/// </summary>
	void Update() override;

	/// <summary>
	/// 開放
	/// </summary>
	void Release() override;

	/// <summary>
	/// 保存
	/// </summary>
	/// <param name="_saveObj">保存データ</param>
	void Save(json& _saveObj) override;

	/// <summary>
	/// 読込
	/// </summary>
	/// <param name="_loadObj">読込データ</param>
	void Load(json& _loadObj) override;

	/// <summary>
	/// ImGuiパネル表示
	/// </summary>
	void DrawData() override;

	/// <summary>
	/// 開始
	/// </summary>
	void Start();

	/// <summary>
	/// 停止
	/// </summary>
	void Stop();

	/// <returns>
	/// 現在の時間(秒)
	/// </returns>
	float GetNowTime();

	/// <returns>
	/// タイマーが終了したか
	/// </returns>
	bool GetIsEnd();

	/// <param name="_time">
	/// カウントする時間(秒)
	/// </param>
	void SetTime(int _time);

	/// <summary>
	/// タイマーをリセット
	/// </summary>
	void Reset();

	/// <returns>
	/// 指定の時間になったらtrue(停止はしない)
	/// </returns>
	/// <param name="_time">通知してほしい時間(秒)</param>
	bool IsOnTime(float _time);

	/// <returns>
	/// 一定時間ごとにtrue
	/// </returns>
	/// <param name="_time">何秒ごとに通知するか(秒)</param>
	bool IsIntervalTime(float _time);

	/// <summary>
	/// 無限にカウントするかどうか
	/// </summary>
	/// <param name="_isInfinity">無限にするか</param>
	void SetInfinity(bool _isInfinity) { isInfinity_ = _isInfinity; }
};

