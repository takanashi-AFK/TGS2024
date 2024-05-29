#pragma once
#include "../Component.h"

class Component_CircleRangeDetector : public Component
{
private:
	
	StageObject* target_;	// 対象オブジェクト
	float radius_;			// 半径
	bool isContains_;		// 当たり判定フラグ

public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="_holder">保有者</param>
	Component_CircleRangeDetector(StageObject* _holder);

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

// setter
	
	/// <param name="_radius">捜索範囲の半径</param>
	void SetRadius(float _radius) { radius_ = _radius; }

	/// <param name="_target">捜索対象</param>
	void SetTarget(StageObject* _target) { target_ = _target; }

// getter

	/// <returns>捜索範囲の半径</returns>
	float GetRadius() { return radius_; }

	/// <returns>捜索対象</returns>
	StageObject* GetTarget() { return target_; }

	/// <returns>捜索対象が捜索範囲内にいたらtrue</returns>
	bool IsContains();

};

