#include "Component_InputMove.h"

// インクルード
#include "../../../../../Engine/GameObject/Camera.h"
#include "../../../../../Engine/DirectX/Input.h"
#include "../../../Camera/TPSCamera.h"
#include "../../StageObject.h"
#include "../StateComponents/Component_StateManager.h"

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

			// カメラの向きを取得
			XMFLOAT2 angle = tpsCamera->GetAngle();

			// カメラの視線ベクトルを取得
			XMVECTOR cameraSightLine = Camera::GetSightLine();

			// 入力による移動方向を取得
			if (Input::IsKey(DIK_W)) {
				moveDir += cameraSightLine;
				isMove_ = true;
			}
		}

		// カメラが存在しない場合
		else {
			// 入力による移動方向を取得
			if (Input::IsKey(DIK_W)) {
				moveDir += XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
				isMove_ = true;
			}
		}

		// 取得した方向ベクトルを正規化
		moveDir = XMVector3Normalize(moveDir);
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
	if(isMove_)
		_stateManager->SetCurrentState(_stateManager->GetStates()["Walk"]);
	else 
		_stateManager->SetCurrentState(_stateManager->GetStates()["Idle"]);
}
