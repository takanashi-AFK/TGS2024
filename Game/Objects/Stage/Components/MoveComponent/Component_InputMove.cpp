#include "Component_InputMove.h"

// インクルード
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

	// 移動中かどうかを初期化
	isMove_ = false;

	// 移動方向を指定
	XMVECTOR moveDir{}; {

		// カメラが存在する場合
		TPSCamera* tpsCamera = (TPSCamera*)holder_->FindObject("TPSCamera");
		if (tpsCamera != nullptr) {

			// 移動方向を計算
			CalcDirection(moveDir, tpsCamera,false);
		}

		// カメラが存在しない場合
		else {
			// 移動方向を計算
			CalcDirection(moveDir);
		}
	}

	// 移動速度を指定
	float moveSpeed = 0.1f;

	// 移動処理
	{
		// 現在の位置を取得
		XMFLOAT3 position = holder_->GetPosition();

		// 移動後の位置を計算
		XMStoreFloat3(&position, XMLoadFloat3(&position) + (moveDir * moveSpeed));

		// 位置を設定
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
	// 移動中かどうかでステートを変更
	if(isMove_)_stateManager->SetCurrentState(_stateManager->GetStates()["Walk"]);
	else _stateManager->SetCurrentState(_stateManager->GetStates()["Idle"]);
}

void Component_InputMove::CalcDirection(XMVECTOR& _dir)
{
	// 入力による移動方向を取得
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

	// 取得した方向ベクトルを正規化
	_dir = XMVector3Normalize(_dir);
}

void Component_InputMove::CalcDirection(XMVECTOR& _dir, TPSCamera* _cam,bool _isYMove)
{
	// カメラの向きを取得
	XMFLOAT2 angle = _cam->GetAngle();

	// カメラの視線ベクトルを取得
	XMVECTOR cameraSightLine = Camera::GetSightLine();
	if(_isYMove == false)cameraSightLine = XMVectorSetY(cameraSightLine, 0.0f);

	// 入力による移動方向を取得
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

	// 取得した方向ベクトルを正規化
	_dir = XMVector3Normalize(_dir);
}
