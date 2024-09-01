#pragma once

// インクルード
#include "Component_Attack.h"
#include <DirectXMath.h>
#include "../../../Engine/Global.h"

using namespace DirectX;

/// <summary>
/// ○〇を撃ち放つ攻撃コンポーネント
/// </summary>
class Component_ShootAttack :public Component_Attack
{
private:
	float shootingSpeed_;			// 弾の速度
	XMVECTOR shootingDirection_;	// 弾の方向
	XMFLOAT3 shootingPosition_;		// 弾の発射位置

	bool isShootPositionSet_;		// 発射位置が設定されているか
	float bulletLifeTime_;				// 弾の生存時間
	EffectData data_;

public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="_holder">コンポーネントの保持者</param>
	Component_ShootAttack(string _name, StageObject* _holder, Component* _parent);
	
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
	/// <param name="_savebj">データの保存情報</param>
	void Save(json& _saveObj) override;
	
	/// <summary>
	/// 読込
	/// </summary>
	/// <param name="_loadObj">データの読込情報</param>
	void Load(json& _loadObj) override;
	
	/// <summary>
	/// ImGuiパネル表示
	/// </summary>
	void DrawData()override;

	/// <summary>
	/// 弾速を設定
	/// </summary>
	/// <param name="_speed">弾速</param>
	void SetShootingSpeed(float _speed) { shootingSpeed_ = _speed; }

	/// <summary>
	/// 弾の方向を設定
	/// </summary>
	/// <param name="_direction">弾の方向</param>
	void SetShootingDirection(XMVECTOR _direction) { shootingDirection_ = _direction; }

	void SetShootingPosition(XMFLOAT3 _position) {
		shootingPosition_ = _position; isShootPositionSet_ = true;
	}

	void SetEffectData(EffectData _data) { data_ = _data; }
};

