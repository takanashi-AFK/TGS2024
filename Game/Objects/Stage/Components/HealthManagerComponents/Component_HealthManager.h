#pragma once
//インクルード
#include"../Component.h"

//作成者-叶内
class Component_HealthManager :public Component {

private:

	int max_;
	int hp_;

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="_holder">保有者</param>
	Component_HealthManager(StageObject* _holder);

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
	void SetHP(int _newHP);

	/// <summary>
	/// ダメージを受けた際の計算
	/// </summary>
	/// <param name="_damageValue">ダメージ値</param>
	void TakeDamage(int _damageValue);

	/// <summary>
	/// 回復の計算
	/// </summary>
	/// <param name="_healValue">回復値</param>
	void Heal(int _healValue);



};