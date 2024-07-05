#pragma once
//インクルード
#include"../Component.h"


/// <summary>
/// ゲージを管理するコンポーネント
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
	Component_Gauge(StageObject* _holder, string _name, ComponentType _type, Component* _parent);
	/// <summary>
	/// HPの値を取得
	/// </summary>
	/// <returns></returns>
	float GetNow() const { return nowGauge_; }

	/// <summary>
	/// HPの値を設定
	/// </summary>
	/// <param name="_newHP">与えられたHP</param>
	void SetNow(float _newNow) { nowGauge_ = _newNow; }

	/// <returns>体力の最大値</returns>
	float GetMax() const { return maxGauge_; }

	/// <summary>
	/// 体力の最大値を設定
	/// </summary>
	void SetMax(float _newMax) { maxGauge_ = _newMax; }

};
