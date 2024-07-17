#include "camera.h"
#include "../DirectX/Direct3D.h"
#include "../../Game/Objects/Stage/StageObject.h"
#include "../../Game/Otheres/GameEditor.h"

XMFLOAT3 _position;
XMFLOAT3 _target;
XMMATRIX _view;
XMMATRIX _proj;
XMMATRIX _billBoard;

//�������i�v���W�F�N�V�����s��쐬�j
void Camera::Initialize()
{
	_position = XMFLOAT3(0, 3, -10);	//�J�����̈ʒu
	_target = XMFLOAT3( 0, 0, 0);	//�J�����̏œ_

	//�v���W�F�N�V�����s��
	_proj = XMMatrixPerspectiveFovLH(XM_PIDIV4, (FLOAT)Direct3D::screenWidth_ / (FLOAT)Direct3D::screenHeight_, 0.1f, 1000.0f);
}

//�X�V�i�r���[�s��쐬�j
void Camera::Update()
{
	// �����|�W�V������null��������
	if (_position.x < -1.0e18f || _position.y < -1.0e18f || _position.z < -1.0e18f ||
		_position.x > 1.0e18f || _position.y > 1.0e18f || _position.z > 1.0e18f ||
		_target.x < -1.0e18f || _target.y < -1.0e18f || _target.z < -1.0e18f ||
		_target.x > 1.0e18f || _target.y > 1.0e18f || _target.z > 1.0e18f)
	{
		Camera::SetPosition({ 0,30,-20 });
		Camera::SetTarget({ 0,-20,20 });
	}

	//�r���[�s��
	_view = XMMatrixLookAtLH(XMVectorSet(_position.x, _position.y, _position.z, 0),
		XMVectorSet(_target.x, _target.y, _target.z, 0), XMVectorSet(0, 1, 0, 0));


	//�r���{�[�h�s��
	//�i��ɃJ�����̕��������悤�ɉ�]������s��B�p�[�e�B�N���ł����g��Ȃ��j
	//http://marupeke296.com/DXG_No11_ComeOnBillboard.html
	_billBoard = XMMatrixLookAtLH(XMVectorSet(0, 0, 0, 0), XMLoadFloat3(&_target)- XMLoadFloat3(&_position), XMVectorSet(0, 1, 0, 0));
	_billBoard = XMMatrixInverse(nullptr, _billBoard);
}

//�œ_��ݒ�
void Camera::SetTarget(XMFLOAT3 target) { _target = target; }
void Camera::SetTarget(float x, float y, float z) { Camera::SetTarget(XMFLOAT3(x, y, z)); }

//�ʒu��ݒ�
void Camera::SetPosition(XMFLOAT3 position) { _position = position; }
void Camera::SetPosition(float x, float y, float z) { Camera::SetPosition(XMFLOAT3(x, y, z)); }


//�œ_���擾
XMFLOAT3 Camera::GetTarget() { return _target; }

//�ʒu���擾
XMFLOAT3 Camera::GetPosition() { return _position; }

//�r���[�s����擾
XMMATRIX Camera::GetViewMatrix() { return _view; }

//�v���W�F�N�V�����s����擾
XMMATRIX Camera::GetProjectionMatrix() { return _proj; }

//�r���{�[�h�p��]�s����擾
XMMATRIX Camera::GetBillboardMatrix(){	return _billBoard; }

XMVECTOR Camera::GetSightLine() { return XMLoadFloat3(&_target) - XMLoadFloat3(&_position); }
