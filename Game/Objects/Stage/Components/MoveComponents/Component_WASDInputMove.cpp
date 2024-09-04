#include "Component_WASDInputMove.h"
#include "../../../../../Engine/directX/Input.h"
#include "../../../../../Engine/ImGui/imgui.h"
#include "../../StageObject.h"
#include "../../../../../Engine/GameObject/Camera.h"
#include "../../../../../Engine/GameObject/GameObject.h"
#include "../../../Camera/TPSCamera.h"
#include <cmath>

namespace
{
	float speed = 0.1f;
}

Component_WASDInputMove::Component_WASDInputMove(string _name, StageObject* _holder, Component* _parent)
	:Component(_holder, _name, WASDInputMove, _parent), isMove_(false)
{
}

void Component_WASDInputMove::Initialize()
{
}

void Component_WASDInputMove::Update()
{

    // このコンポーネントがアクティブでない場合、処理を終了
    if (isActive_ == false) return;
    isMove_ = false;
    // 基本のベクトルを用意、初期化
    dir_ = XMVectorZero();

    TPSCamera* tpsCamera = (TPSCamera*)holder_->FindObject("TPSCamera");
    if (tpsCamera == nullptr) return;

    XMFLOAT2 angle = tpsCamera->GetAngle();

    // カメラの視線ベクトルを取得、Y成分を0にして正規化
    XMVECTOR sightLine = Camera::GetSightLine();
    sightLine = XMVectorSetY(sightLine, 0);
    sightLine = XMVector3Normalize(sightLine);

    // 入力に応じて方向ベクトルを設定
    if (Input::IsKey(DIK_W)) { dir_ += sightLine; isMove_ = true; holder_->SetRotateY(angle.y - 25); }
    if (Input::IsKey(DIK_A)) { dir_ += XMVector3Transform(sightLine, XMMatrixRotationY(XMConvertToRadians(-90))); isMove_ = true; holder_->SetRotateY((angle.y - 25) - 90); }
    if (Input::IsKey(DIK_S)) { dir_ += -sightLine; isMove_ = true; holder_->SetRotateY((angle.y - 25) + 180); }
    if (Input::IsKey(DIK_D)) { dir_ += XMVector3Transform(sightLine, XMMatrixRotationY(XMConvertToRadians(90))); isMove_ = true; holder_->SetRotateY((angle.y - 25) + 90);}

    XMFLOAT3 padMove = Input::GetPadStickL();
    
	XMVECTOR padDir = XMVectorSet(padMove.x, 0, padMove.y, 0);


    if (!XMVector3Equal(padDir, XMVectorZero())) {

        dir_ = XMVector3Normalize(padDir);

        float angle = std::atan2(XMVectorGetX(dir_),XMVectorGetZ(dir_));

        holder_->SetRotateY(XMConvertToDegrees(angle));
        isMove_ = true;

    }

	

    dir_ = XMVector3Normalize(dir_);
    XMVECTOR move = dir_ * speed;

    // 移動ベクトルをXMFLOAT3に変換
	XMFLOAT3 pos = holder_->GetPosition();
    XMStoreFloat3(&pos,XMLoadFloat3(&pos)+move);

    // 新しい位置を設定
    holder_->SetPosition(pos);
}

void Component_WASDInputMove::Release()
{
}

void Component_WASDInputMove::DrawData()
{
	ImGui::Checkbox("Active", &isActive_);
	ImGui::SliderFloat("Speed", &speed, 0.01f, 1.0f);
}

void Component_WASDInputMove::Save(json& _saveObj)
{
	_saveObj["isActive_"] = isActive_;
	_saveObj["speed_"] = speed;
}

void Component_WASDInputMove::Load(json& _loadObj)
{
	if(_loadObj.contains("isActive_"))isActive_ = _loadObj["isActive_"];
    if(_loadObj.contains("speed_"))speed = _loadObj["speed_"];
}

void Component_WASDInputMove::Move(XMVECTOR _dir, float _speed)
{
	XMFLOAT3 pos = holder_->GetPosition();
	XMStoreFloat3(&pos, XMLoadFloat3(&pos) + _dir * _speed);
	holder_->SetPosition(pos);
}
