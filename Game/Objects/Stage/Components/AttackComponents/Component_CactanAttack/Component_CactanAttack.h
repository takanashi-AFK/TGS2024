#pragma once

// インクルード
#include "../Component_Attack.h"

/// <summary>
/// カクタン(遠距離攻撃Enemy)の攻撃コンポーネント
/// </summary>
class Component_CactanAttack :public Component_Attack
{
private:
	float bulletSpeed_;	 // 弾の速度
	StageObject* target_;// 攻撃対象
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="_holder">コンポーネントの保持者</param>
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
	/// <param name="_savebj">データの保存情報</param>
	void Save(json& _saveObj) override;
	
	/// <summary>
	/// 読込
	/// </summary>
	/// <param name="_loadObj">データの読込情報</param>
	void Load(json& _loadObj) override;
	
	/// <summary>
	/// ImGuiパネル表示
	/// </summary>
	void DrawData()override;

	/// <summary>
	/// 攻撃実行
	/// </summary>
	void Attack();

	/// <summary>
	/// ターゲットの設定
	/// </summary>
	void SetTarget();
};

