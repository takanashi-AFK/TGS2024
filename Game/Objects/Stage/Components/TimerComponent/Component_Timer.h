#pragma once

// インクルード
#include "../Component.h"

// 作成者-高梨

/// <summary>
/// タイマーを管理するコンポーネント
/// </summary>
class Component_Timer : public Component
{
private:

	float maxTime_;
	float nowTime_;
	float tempMax_;
	bool isEnd_;
	bool countNow_;
	bool isInfinity_;

public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="_holder">保有者</param>
	Component_Timer(StageObject* _holder);

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
	/// <param name="_saveObj">保存情報</param>
	void Save(json& _saveObj) override;

	/// <summary>
	/// 読込
	/// </summary>
	/// <param name="_loadObj">読込情報</param>
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

	/// <returns>現在の時間(秒)</returns>
	float GetNowTime();

	/// <returns>タイマーが終了したか</returns>
	bool GetIsEnd();

	/// <param name="_time">カウントする時間(秒)</param>
	void SetTime(int _time);

	/// <summary>
	/// タイマーをリセット
	/// </summary>
	void Reset();

	/// <param name="_time">通知してほしい時間(秒)</param>
	/// <returns>指定の時間になったらtrue(停止はしない)</returns>
	bool IsOnTime(float _time);


	/// <param name="_time">何秒ごとに通知するか(秒)</param>
	/// <returns>一定時間ごとにtrue</returns>
	bool IsIntervalTime(float _time);

	/// <summary>
	/// 無限にカウントするかどうか
	/// </summary>
	void SetInfinity(bool _isInfinity) { isInfinity_ = _isInfinity; }

};

