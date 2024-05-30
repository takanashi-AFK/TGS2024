#pragma once
// インクルード
#include "../Component.h"

/// <summary>
/// 円形範囲に入った対象を検出するコンポーネント
/// </summary>
class Component_CircleRangeDetector : public Component
{
private:
	
	StageObject* target_;	// 検出対象
	float radius_;			// 検出範囲の半径
	bool isContains_;		// 検出フラグ

public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="_holder">保有者</param>
	Component_CircleRangeDetector(string _name, StageObject* _holder);

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
	
	/// <param name="_radius">
	/// 捜索範囲の半径
	/// </param>
	void SetRadius(float _radius) { radius_ = _radius; }

	/// <param name="_target">
	/// 捜索対象
	/// </param>
	void SetTarget(StageObject* _target) { target_ = _target; }

	/// <returns>
	/// 捜索範囲の半径
	/// </returns>
	float GetRadius() { return radius_; }

	/// <returns>
	/// 捜索対象
	/// </returns>
	StageObject* GetTarget() { return target_; }

	/// <returns>
	/// 捜索対象が捜索範囲内にいたらtrue
	/// </returns>
	bool IsContains();

};

