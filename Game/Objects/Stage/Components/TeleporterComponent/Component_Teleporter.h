#pragma once

//インクルード
#include "../Component.h"
#include "../../StageObject.h"
#include <string>
class Component_Teleporter : public Component
{
private:
	StageObject* target_;
	string targetName_;
	XMFLOAT3 teleportPosition_; // テレポート先の座標
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="_holder">保有者</param>
	Component_Teleporter(string _name, StageObject* _holder, Component* _parent);

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
	/// ImGuiパネル表示
	/// </summary>
	void DrawData() override;

	/// <summary>
   /// 衝突処理
   /// </summary>
   /// <param name="_target">衝突対象</param>
	void Teleport(GameObject* _target);

	/// <summary>
	/// テレポート先を設定
	/// </summary>
	/// <param name="position">テレポート先の座標</param>
	void SetTeleportPosition(const XMFLOAT3& position);
};