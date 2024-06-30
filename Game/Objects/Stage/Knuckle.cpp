#include "Knuckle.h"
#include "../../../Engine/ResourceManager/Model.h"
#include "../../../Engine/GameObject/Camera.h"

namespace
{
	const int FPS = 60;
}

Knuckle::Knuckle(GameObject* _parent) :
	StageObject("Knuckle", "Models/DebugCollision/SphereCollider.fbx", _parent), frame_(), isEnd_(true)
{
}

void Knuckle::Initialize()
{
    // コライダーの中心を設定 
    XMFLOAT3 colliderCenter = XMFLOAT3(0, 0, 0);

    // コライダーのサイズを設定
    XMFLOAT3 colliderSize = XMFLOAT3(3, 1, 3);

	// 

    // BoxColliderのコンストラクタを呼び出してコライダーを追加
    BoxCollider* collider = new BoxCollider(colliderCenter, colliderSize);
    AddCollider(collider);

    // モデルの読み込み
    modelHandle_ = Model::Load(modelFilePath_);
    assert(modelHandle_ >= 0);
}

void Knuckle::Update()
{
	AutoDelete(0.1f);
}

void Knuckle::Release()
{
}

void Knuckle::Draw()
{
}

void Knuckle::AutoDelete(float _sec)
{
	// 0以下なら終了
	if (_sec <= 0)return;

	// 経過フレームが指定秒数を超えたら削除
	if (frame_ > FPS * _sec) {
		KillMe();
		isEnd_ = true;
	}
	else frame_++;
}


