#pragma once
#include "../Component.h"

// X方向に平行移動を行うコンポーネントのクラス
class MoveXComponent : public Component
{
private:
	float moveSpeedX_;	// 移動速度

public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="_holeder">保有者</param>
	MoveXComponent(StageObject* _holeder);

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
	/// ImGui表示
	/// </summary>
	void DrawData() override;
};

