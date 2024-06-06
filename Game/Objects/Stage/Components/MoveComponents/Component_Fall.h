#pragma once

//インクルード
#include "../Component.h"
#include <DirectXMath.h>

// usingディレクティブ
using namespace DirectX;

/// <summary>
/// オブジェクトの降下・上昇を行うコンポーネントのクラス
/// </summary>
class Component_Fall : public Component
{
private:
	enum STATE { FALL, RISE, WAIT, };	// 状態
	STATE nowState_ ;					// 現在の状態	
	STATE prevState_;					// １フレーム前の状態

	float fallSpeed_;					// 降下速度
	float riseSpeed_;					// 上昇速度
	float fallDistance_;				// 降下する距離

	float startHeight_;					// 開始の高さ

	float startRiseHeight_;				// 上昇開始の高さ
	float startFallHeight_;				// 降下開始の高さ
	bool isActive_;						// 実行されたかどうか

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="_holder">保有者</param>
	Component_Fall(string _name, StageObject* _holder, Component* _parent);

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
	/// 降下の開始
	/// </summary>
	void Execute() { isActive_ = true; }

	/// <summary>
	/// 降下の停止
	/// </summary>
	void Stop() { isActive_ = false; }

	/// <summary>
	/// 実行されているかどうか
	/// </summary>
	bool IsActived() { return isActive_; }

	void SetState(STATE _state) { prevState_ = nowState_; nowState_ = _state; }

	bool IsFalling() { return nowState_==FALL ? true:false; }
private:
	void FallMove(float& _height);	//降下
	void RiseMove(float& _height);	//上昇
	void Wait();	//待機
};

