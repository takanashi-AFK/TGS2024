#pragma once
//インクルード
#include"Component_Gauge.h"

/// <summary>
/// 体力の増減を管理するコンポーネント
/// </summary>
class Component_HealthGauge :public Component_Gauge
{
private:
	float prev_;	//前回の体力
	float shaderChangeTime_;	//シェーダーを変更する時間
	bool isLock_;	//ロックフラグ
	bool isTakeDamage_;	//ダメージを受けたか
public:
	/// <summary> コンストラクタ </summary>
	Component_HealthGauge(string _name, StageObject* _holder, Component* _parent);

	/// <summary> 初期化 </summary>
	void Initialize() override;

	/// <summary> 更新 </summary>
	void Update() override;

	/// <summary> 解放 </summary>
	void Release() override;
/*
setter :*/
	/// <summary> ダメージを受ける </summary>
	void TakeDamage(float _damageValue);

	/// <summary> 回復 </summary>
	void Heal(float _healValue);

	/// <summary> ロック </summary>
	void Lock() { isLock_ = true; }

	/// <summary> アンロック </summary>
	void Unlock() { isLock_ = false; }
/*
predicate :*/
	/// <summary> 死亡判定 </summary>
	bool IsDead() const { return now_ <= 0; }

	/// <summary> ロック中か </summary>
	bool IsLock() const { return isLock_; }

	/// <summary> ロック中かつ減少中か </summary>
	bool IsLockAndReduce()const { return isLock_ && isTakeDamage_; }

	/// <summary> ダメージを受けたか </summary>
	bool IsTakeDamage() const { return isTakeDamage_; }
};