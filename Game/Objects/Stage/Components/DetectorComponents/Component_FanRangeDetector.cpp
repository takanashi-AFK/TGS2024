#include "Component_FanRangeDetector.h"
#include "../../StageObject.h"

Component_FanRangeDetector::Component_FanRangeDetector(StageObject* _holder)
	: Component(_holder, "Component_FanRangeDetector", FanRangeDetector)
	, target_(nullptr)
{
}

void Component_FanRangeDetector::Initialize()
{
}

void Component_FanRangeDetector::Update()
{
}

void Component_FanRangeDetector::Release()
{
}

void Component_FanRangeDetector::Save(json& _saveObj)
{
}

void Component_FanRangeDetector::Load(json& _loadObj)
{
}

void Component_FanRangeDetector::DrawData()
{
}

bool Component_FanRangeDetector::Contains()
{
	//	対象が存在しない場合は処理を行わない
	if (target_ == nullptr)return false;

	//	扇形範囲判定
	
	// 保有者の位置から対象の位置へのベクトル
	XMVECTOR holderPositionToTargetPosition = 
		XMVectorSetY(XMLoadFloat3(&target_->GetPosition()),0) - XMVectorSetY(XMLoadFloat3(&holder_->GetPosition()), 0);

	// 保有者の位置から対象の位置へのベクトルの長さ
	float length = XMVectorGetX(XMVector3Length(holderPositionToTargetPosition));

	
}
