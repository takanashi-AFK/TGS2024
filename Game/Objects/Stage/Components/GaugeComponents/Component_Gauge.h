#pragma once
//インクルード
#include"../Component.h"


/// <summary>
/// 体力の増減を管理するコンポーネント
/// </summary>
class Component_Gauge :public Component
{
private:

	float maxGauge_; //ゲージの上限
	float nowGauge_;  //現在のゲージ

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="_holder">保有者</param>
	Component_Gauge(string _name, StageObject* _holder, ComponentType _type, Component* _parent);

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
	/// ゲージの値を取得
	/// </summary>
	/// <returns></returns>
	float GetGauge() const;

	/// <summary>
	/// ゲージの値を設定
	/// </summary>
	/// <param name="_newHP">与えられたHP</param>
	void SetGauge(float _newGauge);

	/// <returns>ゲージの最大値</returns>
	float GetMax() const;

	/// <summary>
	/// ゲージの最大値を設定
	/// </summary>
	void SetMax(float _newMaxGauge);

	/// <summary>
	/// ゲージのリセット(最大値に戻す)
	/// </summary>
	void Reset();
};
