#pragma once

// インクルード
#include "../Component.h"

// 作成者-高梨
class Component_Timer : public Component
{
private:

	float time_;
	float nowTime_;
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
	/// ImGui表示
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

	/// <returns>現在の時間</returns>
	float GetNowTime();

	/// <summary>
	/// タイマーが終了したか
	/// </summary>	/// <returns>終了したらtrue</returns>
	bool GetEnd();

	/// <param name="_time">カウントする秒数</param>
	void SetTime(int _time);

	/// <summary>
	/// タイマーをリセット
	/// </summary>
	void Reset();

	/// <summary>
	/// 指定の時間になったら通知
	/// </summary>
	/// <param name="_time"></param>
	/// <returns></returns>
	bool IsOnTime(float _time);

	/// <summary>
	/// 一定時間ごとに通知
	/// </summary>
	/// <param name="_time"></param>
	/// <returns></returns>
	float IsIntervalTime(float _time);

};

