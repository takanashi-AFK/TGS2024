#include "Component_Chase.h"
#include "../../StageObject.h"
Component_Chase::Component_Chase(StageObject* _holder)
	:Component(_holder,"Component_Chase",ChaseComponent),move_(0.0f),target_(nullptr)
{
}

void Component_Chase::Initialize()
{
	target_->FindObject("target_");
	
}

void Component_Chase::Update()
{
	Chase();

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

void Component_Chase::Chase()
{
	XMFLOAT3 targetPos = target_->GetPosition();
	XMFLOAT3 holderPos = holder_->GetPosition();

	XMVECTOR targetVec = XMLoadFloat3(&targetPos);
	XMVECTOR holderVec = XMLoadFloat3(&holderPos);

	XMVECTOR chaseDirection = XMVector3Normalize(XMVectorSetY(targetVec - holderVec, 0));

	double rotateangle = atan2(XMVectorGetX(-chaseDirection), XMVectorGetZ(-chaseDirection));

	holder_->SetRotateY(rotateangle);

	XMStoreFloat3(&holderPos, holderVec + (chaseDirection * move_));

	holder_->SetPosition(holderPos);
}
