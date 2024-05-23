#pragma once
#include"../../Component.h"
#include"../Component_Attack.h"
#include"../../../../../../Engine/GameObject/GameObject.h"
//作成者:高梨
class Component_CactanAttack :public Component_Attack
{
	int frame;

	public:
	 	Component_CactanAttack(StageObject* _holder);
	 	
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

