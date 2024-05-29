

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

	/// <summary>
	/// 落下の開始
	/// </summary>
	void Start() { isActive_ = true; }
	/// <summary>
	/// 落下の停止
	/// </summary>
	void Stop() { isActive_ = false; }

	/// <summary>
	/// 実行されているかどうか
	/// </summary>
	void Execute() { isActive_ = true; }
};

