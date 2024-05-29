#pragma once

//インクルード
#include"../Component.h"

//作成者:高梨
class Component_Attack :public Component
{

protected:
	bool isAttack_;//攻撃フラグ
	int  power_;//攻撃力
private:

public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="_holder">保有者</param>
	Component_Attack(StageObject* _holder);


	/// <summary>
	/// ほかコンポーネントを継承した際のコンストラクタ
	/// </summary>
	/// <param name="_holder">保有者</param>
	/// <param name="_name">自身のコンポーネント名</param>
	/// <param name="_type">自身のコンポーネントID</param>
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

	/// <summary>
	/// ImGuiパネル表示
	/// </summary>
	void DrawData()override;

};

