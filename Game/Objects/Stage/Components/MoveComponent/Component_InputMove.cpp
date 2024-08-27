#include "Component_InputMove.h"

// �C���N���[�h
#include "../../../../../Engine/GameObject/Camera.h"
#include "../../../../../Engine/DirectX/Input.h"
#include "../../../Camera/TPSCamera.h"
#include "../../StageObject.h"
#include "../StateManagerComponent/Component_StateManager.h"

Component_InputMove::Component_InputMove(string _name, StageObject* _holder, Component* _parent)
	: Component(_holder, _name, ComponentType::InputMove, _parent)
{
}

void Component_InputMove::Initialize()
{
	StateObserver::Entry(holder_);
}

void Component_InputMove::Update()
{
	if (isEntryObserver_ == false)isEntryObserver_ = StateObserver::Entry(holder_);

	// �ړ������ǂ�����������
	isMove_ = false;

	// �ړ��������w��
	XMVECTOR moveDir{}; {

		// �J���������݂���ꍇ
		TPSCamera* tpsCamera = (TPSCamera*)holder_->FindObject("TPSCamera");
		if (tpsCamera != nullptr) {

			// �ړ��������v�Z
			CalcDirection(moveDir, tpsCamera,false);
		}

		// �J���������݂��Ȃ��ꍇ
		else {
			// �ړ��������v�Z
			CalcDirection(moveDir);
		}
	}

	// �ړ����x���w��
	float moveSpeed = 0.1f;

	// �ړ�����
	{
		// ���݂̈ʒu���擾
		XMFLOAT3 position = holder_->GetPosition();

		// �ړ���̈ʒu���v�Z
		XMStoreFloat3(&position, XMLoadFloat3(&position) + (moveDir * moveSpeed));

		// �ʒu��ݒ�
		holder_->SetPosition(position);
	}
}

void Component_InputMove::Release()
{
}

void Component_InputMove::Save(json& _saveObj)
{
}

void Component_InputMove::Load(json& _loadObj)
{
}

void Component_InputMove::DrawData()
{
}

void Component_InputMove::OnStateChange(Component_StateManager* _stateManager)
{
	// �ړ������ǂ����ŃX�e�[�g��ύX
	if(isMove_)_stateManager->SetCurrentState(_stateManager->GetStates()["Walk"]);
	else _stateManager->SetCurrentState(_stateManager->GetStates()["Idle"]);
}

void Component_InputMove::CalcDirection(XMVECTOR& _dir)
{
	// ���͂ɂ��ړ��������擾
	if (Input::IsKey(DIK_W)) {
		_dir += XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
		isMove_ = true;
	}

	if (Input::IsKey(DIK_S)) {
		_dir += XMVectorSet(0.0f, 0.0f, -1.0f, 0.0f);
		isMove_ = true;
	}

	if (Input::IsKey(DIK_A)) {
		_dir += XMVectorSet(-1.0f, 0.0f, 0.0f, 0.0f);
		isMove_ = true;
	}

	if (Input::IsKey(DIK_D)) {
		_dir += XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f);
		isMove_ = true;
	}

	// �擾���������x�N�g���𐳋K��
	_dir = XMVector3Normalize(_dir);
}

void Component_InputMove::CalcDirection(XMVECTOR& _dir, TPSCamera* _cam,bool _isYMove)
{
	// �J�����̌������擾
	XMFLOAT2 angle = _cam->GetAngle();

	// �J�����̎����x�N�g�����擾
	XMVECTOR cameraSightLine = Camera::GetSightLine();
	if(_isYMove == false)cameraSightLine = XMVectorSetY(cameraSightLine, 0.0f);

	// ���͂ɂ��ړ��������擾
	if (Input::IsKey(DIK_W)) {
		_dir += cameraSightLine;
		isMove_ = true;
	}

	if (Input::IsKey(DIK_S)) {
		_dir += -cameraSightLine;
		isMove_ = true;
	}

	if (Input::IsKey(DIK_A)) {
		_dir += XMVector3Transform(cameraSightLine,XMMatrixRotationY(XMConvertToRadians(-90.0f)));
		
		isMove_ = true;
	}

	if (Input::IsKey(DIK_D)) {
		_dir += XMVector3Transform(cameraSightLine, XMMatrixRotationY(XMConvertToRadians(90.0f)));
		isMove_ = true;
	}

	// �擾���������x�N�g���𐳋K��
	_dir = XMVector3Normalize(_dir);
}
