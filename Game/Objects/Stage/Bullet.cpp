#include "Bullet.h"
#include "../../../Engine/ResourceManager/Model.h"
#include "../../../Engine/ImGui/imgui.h"
Bullet::Bullet(GameObject* _parent) 
:StageObject("Bullet","Models/DebugCollision/SphereCollider.fbx", _parent),isShot_(false),frame(0)
{
}

Bullet::~Bullet()
{
}

void Bullet::Initialize()
{
	modelHandle_ = Model::Load(modelFilePath_);
	assert(modelHandle_ >= 0);

	//サイズは後で変更
	collision = new SphereCollider(transform_.position_, 1.0f);
	AddCollider(collision);
	transform_.scale_ = XMFLOAT3(0.3,0.3,0.3);
}


void Bullet::Update()
{
	transform_.position_.x += Move_Position.x;
	transform_.position_.y += Move_Position.y;
	transform_.position_.z += Move_Position.z;	
	if (frame>60) {
		frame = 0;
		KillMe();
	}
	else
		frame++;
	
}

void Bullet::Draw()
{
	Model::SetTransform(modelHandle_, transform_);
	Model::Draw(modelHandle_);
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

void Bullet::TestAttack()
{
	transform_.position_.x += Move_Position.x;
	transform_.position_.y += Move_Position.y;
	transform_.position_.z += Move_Position.z;
}


