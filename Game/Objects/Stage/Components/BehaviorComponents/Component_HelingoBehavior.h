#pragma once
#include "../Component.h"

class Component_HelingoBehavior : public Component
{
private:
	StageObject* target_;	// ターゲット
	string targetName_;		// ターゲット名

	float fallrange_;		// 落下範囲
	float discoveryrange_;			// 発見範囲
	bool isTimerActive_;	// タイマーがアクティブかどうか

	bool oneHit_;
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>	
	/// <param name="_holder">保有者</param>
	Component_HelingoBehavior(string _name, StageObject* _holder, Component* _parent);
	
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
	/// 衝突処理
	/// </summary>
	void OnCollision(GameObject* _target, Collider* _collider) override;

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
	/// ImGuiパネル表示
	/// </summary>
	void DrawData() override;
};

