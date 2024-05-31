#pragma once

//インクルード
#include"../Component.h"

/// <summary>
/// 攻撃コンポーネントの基底クラス
/// </summary>
class Component_Attack :public Component
{
protected:
	bool isAttack_; //攻撃フラグ
	int  power_;	//攻撃力

public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="_holder">保有者</param>
	/// <param name="_name">自身のコンポーネント名</param>
	/// <param name="_type">自身のコンポーネントタイプ</param>
	Component_Attack(StageObject* _holder, string _name, ComponentType _type,Component* _parent);
};
