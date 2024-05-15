#include "Component_Chase.h"
#include "../../StageObject.h"
Component_Chase::Component_Chase(StageObject* _holder)
	:Component(_holder,"Component_Chase",Chase),move_(0.0f),target_(nullptr)
{
}

void Component_Chase::Initialize()
{
}

void Component_Chase::Update()
{
	ChaseMove();

}

void Component_Chase::Release()
{
}

void Component_Chase::Save(json& _saveobj)
{
	_saveobj["move_"] = move_;
	if (target_ != nullptr)_saveobj["targetName"] = target_->GetObjectName();
}

void Component_Chase::Load(json& _loadobj)
{
	if (_loadobj.find("move_") != _loadobj.end())move_ = _loadobj["move"];
	if (_loadobj.find("target_") != _loadobj.end())target_ = (StageObject*)holder_->FindObject(_loadobj["target_"]);
}

void Component_Chase::ChaseMove()
{
	if(target_ == nullptr)return;

	//対象と保有者のポジションを取得
	XMFLOAT3 targetPos = target_->GetPosition();
	XMFLOAT3 holderPos = holder_->GetPosition();

	//ポジションをVector型に変更し追従する方向を決める
	XMVECTOR targetVec = XMLoadFloat3(&targetPos);
	XMVECTOR holderVec = XMLoadFloat3(&holderPos);
	XMVECTOR chaseDirection = XMVector3Normalize(XMVectorSetY(targetVec - holderVec, 0));

	//追従する方向に体の向きを回転させる
	double rotateangle = atan2(XMVectorGetX(-chaseDirection), XMVectorGetZ(-chaseDirection));
	holder_->SetRotateY(rotateangle);

	//移動後の位置を求める　自分のポジション+(向き*移動量)
	XMStoreFloat3(&holderPos, holderVec + (chaseDirection * move_));

	//移動後の位置を適応
	holder_->SetPosition(holderPos);
}
