#include "Bullet.h"

Bullet::Bullet(GameObject* parent)
	:GameObject(parent, "Bullet"),collision(nullptr)
{
}

Bullet::~Bullet()
{
}

void Bullet::Initialize()
{
	//サイズは後で変更
	collision = new SphereCollider(transform_.position_, 0.0f);
	AddCollider(collision);
	transform_.scale_ = XMFLOAT3(0.1f, 0.1f, 0.1f);
}

void Bullet::Update()
{
	transform_.position_.x += Move_Position.x;
	transform_.position_.y += Move_Position.y;
	transform_.position_.z += Move_Position.z;
}

void Bullet::Draw()
{
}

void Bullet::Release()
{
}

void Bullet::Attack(XMFLOAT3 _playerPosition, XMVECTOR _direction)
{
	transform_.position_ = _playerPosition;
	XMVECTOR shotDirection = XMVector3Normalize(_direction);
	XMStoreFloat3(&Move_Position, shotDirection * BULLET_SPEED);
}
