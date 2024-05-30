#pragma once
//インクルード
#include "../Component.h"

/// <summary>
/// X方向に平行移動を行うコンポーネントのクラス
/// </summary>
class Component_MoveX : public Component
{
private:
	float moveSpeedX_;	// 移動速度

public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="_holder">保有者</param>
	Component_MoveX(string _name, StageObject* _holder);

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
};

