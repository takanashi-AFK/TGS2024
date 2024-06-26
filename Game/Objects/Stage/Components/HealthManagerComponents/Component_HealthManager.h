#pragma once
//インクルード
#include"../Component.h"


/// <summary>
/// 体力の増減を管理するコンポーネント
/// </summary>
class Component_HealthManager :public Component 
{
private:

	float max_; //体力の上限
	float hp_;  //体力

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="_holder">保有者</param>
	Component_HealthManager(string _name, StageObject* _holder, Component* _parent);

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
	/// HPの値を取得
	/// </summary>
	/// <returns></returns>
	float GetHP() const;

	/// <summary>
	/// HPの値を設定
	/// </summary>
	/// <param name="_newHP">与えられたHP</param>
	void SetHP(float _newHP);

	/// <returns>体力の最大値</returns>
	float GetMax() const;

	/// <summary>
	/// 体力の最大値を設定
	/// </summary>
	void SetMax(float _newMax);

	/// <summary>
	/// ダメージを受けた際の計算
	/// </summary>
	/// <param name="_damageValue">ダメージ値</param>
	void TakeDamage(float _damageValue);

	/// <summary>
	/// 回復の計算
	/// </summary>
	/// <param name="_healValue">回復値</param>
	void Heal(float _healValue);

	/// <summary>
	/// 体力のリセット(最大値に戻す)
	/// </summary>
	void Reset();
};