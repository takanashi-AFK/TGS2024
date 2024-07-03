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
	
};
