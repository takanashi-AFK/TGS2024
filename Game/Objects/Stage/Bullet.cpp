#include "Bullet.h"

// インクルード
#include "../../../Engine/Global.h"
#include "../../../Engine/ImGui/imgui.h"
#include "../../../Engine/ResourceManager/Model.h"
//#include "Components/GaugeComponents/Component_HealthGauge.h"
#include "Stage.h"

Bullet::Bullet(GameObject* _parent) 
:StageObject("Bullet","Models/DebugCollision/SphereCollider.fbx", _parent),isActive_(false), frame_(), speed_(), direction_()
{
}

void Bullet::Initialize()
{
	// コライダーを追加
	AddCollider(new SphereCollider(XMFLOAT3(0, 0, 0), 0.5f));

	// モデルの読み込み
	modelHandle_ = Model::Load(modelFilePath_);
	assert(modelHandle_ >= 0);

	//SetScale(0.2f);

	// effekseer: :Effectの読み込み
	EFFEKSEERLIB::gEfk->AddEffect("Sylph10", "Effects/Sylph10.efk");/*★★★*/

	// effekseer: :Effectの再生情報の設定
	EFFEKSEERLIB::EFKTransform t;/*★★★*/
	DirectX::XMStoreFloat4x4(&(t.matrix), transform_.GetWorldMatrix());/*★★★*/
	t.isLoop = false;/*★★★*/
	t.maxFrame = 180;/*★★★*/
	t.speed = 1.f;/*★★★*/


	// effekseer: :Effectの再生
	mt = EFFEKSEERLIB::gEfk->Play("Sylph10", t);/*★★★*/

}

void Bullet::Update()
{
	// 動作中でなければ終了
	if (isActive_ == false)return;

	// 移動
	Move(direction_,speed_);

	// 自動削除
	//if (EFFEKSEERLIB::gEfk->IsEffectPlaying("Sylph10") == false)KillMe();
	AutoDelete(2.f);

	// effekseer: :Effectの再生情報の更新
	DirectX::XMStoreFloat4x4(&(mt->matrix), this->GetWorldMatrix());/*★★★*/
}

void Bullet::Draw()
{
	// モデルの描画
	//Model::SetTransform(modelHandle_, transform_);
	//Model::Draw(modelHandle_);
}

void Bullet::OnCollision(GameObject* _target, Collider* _collider)
{
	if (isActive_ == false)return;

	// ターゲットがStageObjectでない場合は処理を行わない
	StageObject* target = dynamic_cast<StageObject*>(_target);
	if (!target) return;

	if (target->GetObjectName() == shooter_->GetObjectName())return;
	//auto list = target->FindComponent(HealthGauge);

	//if (list.empty()) return;
	//// ダメージ処理
	//for (auto hm : list) {

	//	((Component_HealthGauge*)hm)->TakeDamage(20);
	//	this->KillMe();

	//	if (((Component_HealthGauge*)hm)->IsDead()) {
	//		((Stage*)FindObject("Stage"))->DeleteStageObject((StageObject*)_target);
	//	}
	//}

}

void Bullet::Move(XMVECTOR _dir, float _speed)
{
	// 移動
	XMStoreFloat3(&transform_.position_, XMLoadFloat3(&transform_.position_) + (XMVector3Normalize(_dir) * _speed));
}

void Bullet::AutoDelete(float _sec)
{
	// 0以下なら終了
	if (_sec <= 0)return;

	// 経過フレームが指定秒数を超えたら削除
	if (frame_ > FPS * _sec) KillMe();
	else frame_++;
}

