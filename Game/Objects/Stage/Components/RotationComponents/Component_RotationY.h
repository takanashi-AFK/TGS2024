#pragma once

// インクルード
#include "../Component.h"

// Y軸回転を行うコンポーネントのクラス
class Component_RotationY : public Component
{
private:
	float rotateSpeed_;	// 回転速度
	float angle_;		// 角度

public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="_holder">保有者</param>
	Component_RotationY(StageObject* _holder);
	
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

	
	/// <returns>
	///回転の速度を取得
	///</returns>
	float GetRotateSpeed() { return rotateSpeed_; }

	
	/// <returns>
	///アングルを取得
	/// </returns>
	float GetAngle() { return angle_; }

	/// <summary>
	/// 
	/// </summary>
	/// <param name="_rotateSpeed"></param>
	void SetRotationSpeed(float _rotateSpeed) { rotateSpeed_ = _rotateSpeed; }
	void SetAngle(float _angle) { angle_ = _angle; }

};

