#include "Component_Chase.h"
#include "../../StageObject.h"
Component_Chase::Component_Chase(StageObject* _holder)
	:Component(_holder,"Component_Chase",Chase), movingdistance_(0.0f),target_(nullptr)
{
}

void Component_Chase::Initialize()
{
	movingdistance_ = 0.3f;
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
	_saveobj[" movingdistance_"] = movingdistance_;
	if (target_ != nullptr)_saveobj["targetName"] = target_->GetObjectName();
}

void Component_Chase::Load(json& _loadobj)
{
	if (_loadobj.find("move_") != _loadobj.end()) movingdistance_ = _loadobj[" movingdistance_"];
	if (_loadobj.find("target_") != _loadobj.end())target_ = (StageObject*)holder_->FindObject(_loadobj["target_"]);
}

void Component_Chase::ChaseMove()
{
	if(target_ == nullptr)return;

	//対象と保有者のポジションを取得
	XMFLOAT3 targetPos = target_->GetPosition();
	XMFLOAT3 holderPos = holder_->GetPosition();

	//距離計算
	float chasedist = sqrt((targetPos.x - targetPos.x) * (targetPos.x - targetPos.x) + (targetPos.z - targetPos.z) * (targetPos.z - targetPos.z));
	
	//ポジションをVector型に変更し追従する方向と長さを決める
	XMVECTOR targetVec = XMLoadFloat3(&targetPos);
	XMVECTOR holderVec = XMLoadFloat3(&holderPos);
	float chasedist2 = XMVectorGetX(XMVector3Length(targetVec - holderVec));
	XMVECTOR chaseDirection = XMVector3Normalize(XMVectorSetY(targetVec - holderVec, 0));

	//追従する方向に体の向きを回転させる
	double rotateangle = atan2(XMVectorGetX(-chaseDirection), XMVectorGetZ(-chaseDirection));

	XMStoreFloat3(&holderPos, holderVec + (chaseDirection * movingdistance_));
	if (chasedist2 > 0.5)
	{
		//移動後の位置を適応
		holder_->SetRotateY(rotateangle);
		holder_->SetPosition(holderPos);
	}
	else
	{
		rotateangle = 0;
	}

	
}
