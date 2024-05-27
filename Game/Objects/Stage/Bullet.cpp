#include "Bullet.h"
#include "../../../Engine/ResourceManager/Model.h"
#include "../../../Engine/ImGui/imgui.h"
Bullet::Bullet(GameObject* _parent) 
:StageObject("Bullet","Models/DebugCollision/SphereCollider.fbx", _parent),
frame(0),
speed_(0.f),
direction_(XMVectorSet(0,0,1,0))
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
	if(isActive_){
		XMVECTOR shotDirection = XMVector3Normalize(direction_);
		XMStoreFloat3(&transform_.position_, XMLoadFloat3(&transform_.position_) + (shotDirection * speed_));
		if (frame > FPS) {
			frame = 0;
			isActive_ = false;
			KillMe();
		}
		else
			frame++;
	}
}

void Bullet::Draw()
{
	Model::SetTransform(modelHandle_, transform_);
	Model::Draw(modelHandle_);
}

void Bullet::Release()
{
}

void Bullet::DrawData()
{
}

void Bullet::Save(json& _saveobj)
{
	_saveobj["speed"] = speed_;
}

void Bullet::Load(json& _loadobj)
{
	if(_loadobj.contains("speed"))speed_ = _loadobj["speed"];
}

