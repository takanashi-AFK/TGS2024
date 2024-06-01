#include "Component_WASDInputMove.h"
#include "../../../../../Engine/DirectX/Input.h"
#include "../../StageObject.h"

Component_WASDInputMove::Component_WASDInputMove(string _name, StageObject* _holder, Component* _parent)
	:Component(_holder, _name, WASDInputMove, _parent)
{
}

void Component_WASDInputMove::Initialize()
{
}

void Component_WASDInputMove::Update()
{
	if (Input::IsKey(DIK_W))Move(XMVectorSet(0, 0, 1, 0), 0.1f);
	if (Input::IsKey(DIK_S))Move(XMVectorSet(0, 0, -1, 0), 0.1f);
	if (Input::IsKey(DIK_A))Move(XMVectorSet(-1, 0, 0, 0), 0.1f);
	if (Input::IsKey(DIK_D))Move(XMVectorSet(1, 0, 0, 0), 0.1f);
}

void Component_WASDInputMove::Release()
{
}

void Component_WASDInputMove::Move(XMVECTOR _dir, float _speed)
{
	XMFLOAT3 pos = holder_->GetPosition();
	XMStoreFloat3(&pos, XMLoadFloat3(&pos) + _dir * _speed);
	holder_->SetPosition(pos);
}
