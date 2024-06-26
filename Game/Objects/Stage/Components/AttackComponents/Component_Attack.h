#pragma once

//インクルード
#include"../Component.h"

/// <summary>
/// 攻撃コンポーネントの基底クラス
/// </summary>
class Component_Attack :public Component
{
protected:
	bool isActive_; 
	int  power_;	//攻撃力

public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="_holder">保有者</param>
	/// <param name="_name">自身のコンポーネント名</param>
	/// <param name="_type">自身のコンポーネントタイプ</param>
	Component_Attack(StageObject* _holder, string _name, ComponentType _type,Component* _parent);

	void Execute() { isActive_ = true; }
	void Stop() { isActive_ = false; }
	void SetPower(int _power) { power_ = _power; }
	int GetPower() { return power_; }
};
