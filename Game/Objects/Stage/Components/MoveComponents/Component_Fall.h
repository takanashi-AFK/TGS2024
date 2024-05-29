//

#pragma once

#include "../Component.h"
#include <DirectXMath.h>
class Component_Fall : public Component
{
private:
	
	float fallSpeed_;//降下速度
	float fallSpeedplus_;//降下速度を上げるやつ
	float riseSpeed_;//上昇速度
	float fallDistance_;

	 DirectX::XMFLOAT3 startRisePosition_;
	 DirectX::XMFLOAT3 startFallPosition_;
	
	bool isFirstTime_ = true;
	bool isRising_ = false;
	bool isActive_;
public:
	///<summary>
	/// コンストラクタ
	///</summary>
	///<param name="_holder">保有者</param>
	Component_Fall(StageObject* _holder);

	///<summary>
	/// 初期化
	///</summary>
	void Initialize() override;

	///<summary>
	/// 更新
	///</summary>
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

	// 追従の開始
	void Start() { isActive_ = true; }

	// 追従の停止
	void Stop() { isActive_ = false; }

	void Rising() { isRising_ = true; }

	void Falling() { isRising_ = false; }
	/// <summary>
	/// 攻撃開始
	/// </summary>
	void Execute() { isActive_ = true; }
};

