#pragma once

//インクルード
#include"../Component.h"

//作成者:高梨
class Component_Attack :public Component
{

protected:
	bool isAttack_;
	int  power_;
private:

public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="_holder">保有者</param>
	Component_Attack(StageObject* _holder);

	Component_Attack(StageObject* _holder, string _name, ComponentType _type);

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize() override;

	/// <summary>
	/// 更新
	/// </summary>
	void Update() override;

	/// <summary>
	/// 解放
	/// </summary>
	void Release() override;

	/// <summary>
	/// 保存
	/// </summary>
	/// <param name="_saveobj">データの保存情報</param>
	void Save(json& _saveobj) override;

	/// <summary>
	/// 読み込み
	/// </summary>
	/// <param name="_loadobj">データの読込情報</param>
	void Load(json& _loadobj) override;

	void DrawData()override;

};

