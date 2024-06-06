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

	float fallSpeed_;		//降下速度
	float riseSpeed_;		//上昇速度
	float fallDistance_;	//降下する距離

	float startRiseHeight_;	//上昇開始高さ

	XMFLOAT3 startRisePosition_; //上昇開始位置
	XMFLOAT3 startFallPosition_; //降下開始位置
	
	bool isFirstTime_ = true;	//最初の状態を保存するか
	bool isFalling_ = false;	//落下するかどうか
	bool isRised_ = false;		//上昇するかどうか
	bool isActive_;				//実行されたかどうか



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
	void Start() { isActive_ = true; }

	/// <summary>
	/// 降下の停止
	/// </summary>
	void Stop() { isActive_ = false; }

	/// <summary>
	/// 実行されているかどうか
	/// </summary>
	bool IsActived() { return isActive_; }


	bool IsFalling() { return isFalling_; }
	bool GetIsRised() { return isRised_; }
};

