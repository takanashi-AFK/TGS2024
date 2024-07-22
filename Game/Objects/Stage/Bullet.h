#pragma once

// インクルード
#include "StageObject.h"

// effekseer: インクルード
#include "../../../EffekseeLib/EffekseerVFX.h"/*★★★*/


/// <summary>
/// 発射する弾を管理するクラス
/// </summary>
class Bullet :public StageObject
{
private:
	fs::path effectFilePath_;					// エフェクトファイルのパス
	EFFEKSEERLIB::EFKTransform efkTransform_;	// エフェクトの情報
	std::shared_ptr<EFFEKSEERLIB::EFKTransform> mt;

	bool isActive_;								// アクティブかどうか

	XMVECTOR moveDirection_;					// 移動方向
	float moveSpeed_;							// 移動速度
	StageObject* shooter_;						// 発射したオブジェクト
public:
	Bullet(GameObject* _parent);

	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;

	void Execute();
/*
setter:*/
	void SetDirection(XMVECTOR _direction) { moveDirection_ = _direction; }
	void SetSpeed(float _speed) { moveSpeed_ = _speed; }
	void SetShooter(StageObject* _shooter) { shooter_ = _shooter; }
	void SetEffect(fs::path _efkFilePath, float _isLoop, int _maxFrame, float _speed);
};

Bullet* CreateBullet(GameObject* _parent, fs::path _efkFilePath, float _isLoop, int _maxFrame, float _speed);


