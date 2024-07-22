#include "Bullet.h"

// インクルード

Bullet::Bullet(GameObject* _parent)
	:StageObject("Bullet","Models/DebugCollision/SphereCollider.fbx",_parent)
{
}

void Bullet::Initialize()
{
	// コライダーを追加
	AddCollider(new SphereCollider(XMFLOAT3(0,0,0),0.5f));
}

void Bullet::Update()
{
	// 動作中でなければ処理を行わない
	if (isActive_ == false)return;

	// 移動処理
	XMStoreFloat3(&transform_.position_, XMLoadFloat3(&transform_.position_) + (XMVector3Normalize(moveDirection_) * moveSpeed_));

	// エフェクトの位置情報を更新
	XMStoreFloat4x4(&(mt->matrix), this->GetWorldMatrix());

	// エフェクトが終了したら削除
	if (EFFEKSEERLIB::gEfk->IsEffectEnd(effectFilePath_.filename().string())) KillMe();

}
void Bullet::Draw()
{
}

void Bullet::Release()
{
}

void Bullet::Execute()
{
	isActive_ = true;

	// エフェクトを再生
	EFFEKSEERLIB::gEfk->Play(effectFilePath_.filename().string(), efkTransform_);
}

void Bullet::SetEffect(fs::path _efkFilePath, float _isLoop, int _maxFrame, float _speed)
{
	// エフェクトを読み込む
	effectFilePath_ = _efkFilePath;
	EFFEKSEERLIB::gEfk->AddEffect(effectFilePath_.filename().string(), effectFilePath_.string());

	// エフェクトの位置情報を設定
	XMStoreFloat4x4(&(efkTransform_.matrix), transform_.GetWorldMatrix());

	// エフェクトのループ情報を設定
	efkTransform_.isLoop = _isLoop;

	// エフェクトのマックスフレーム数を設定
	efkTransform_.maxFrame = _maxFrame;

	// エフェクトの再生速度を設定
	efkTransform_.speed = _speed;
}

Bullet* CreateBullet(GameObject* _parent, fs::path _efkFilePath, float _isLoop, int _maxFrame, float _speed)
{
	// 弾を生成
	Bullet* bullet = new Bullet(_parent);

	// エフェクトを設定
	bullet->SetEffect(_efkFilePath, _isLoop, _maxFrame, _speed);

	// 初期化
	bullet->Initialize();

	// 親オブジェクトのリストに追加
	if (_parent != nullptr)_parent->PushBackChild(bullet);

	return bullet;

}
