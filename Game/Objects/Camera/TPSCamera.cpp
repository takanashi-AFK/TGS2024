#include "TPSCamera.h"
#include "../../../Engine/DirectX/Input.h"
#include "../../../Engine/GameObject/Camera.h"


namespace {
    const float DEF_SENSITIVITY = 0.3f;
    const float SENSITIVITY_MAX = 1;
    const float SENSITIVITY_MIN = 0;
}


TPSCamera::TPSCamera(GameObject* parent)
	:GameObject(parent, "TPSCamera"), angle_({ 0,0 }), sensitivity_(DEF_SENSITIVITY), pTarget_(nullptr)
{
}

void TPSCamera::Initialize()
{
}

void TPSCamera::Update()
{
	if (isActive_ == false)return;
    if (pTarget_ == nullptr)return;

    // カメラの焦点・位置を格納する変数を用意
    XMFLOAT3 camTarget{};
    XMFLOAT3 camPosition{};

    // 回転の中心を設定１⃣
    XMFLOAT3 center = pTarget_->GetPosition();
    center.y += 4.f;

    // 回転のための情報を取得
    {
#ifdef _DEBUG
        //ImGui::SliderFloat("sensitivity", &sensitivity_, SENSITIVITY_MIN, SENSITIVITY_MAX);
#endif // _DEBUG
        XMFLOAT3 mouseMove = Input::GetMouseMove();
        angle_.x += mouseMove.y * sensitivity_;
        angle_.y += mouseMove.x * sensitivity_;
        // ｘ軸回転の上限・下限を設定し回転を制限
        {
            const float upperlimit = -80.f;
            if (angle_.x < upperlimit)angle_.x -= mouseMove.y * sensitivity_;
            const float lowerlimit = 80.f;
            if (angle_.x > lowerlimit)angle_.x -= mouseMove.y * sensitivity_;
        }
    }
    // ｙ軸の回転を行うs
    {
        // 回転行列を作成
        XMMATRIX rotateY = XMMatrixRotationY(XMConvertToRadians(angle_.y));

        // ↑の行列を元に回転
        XMVECTOR center_To_camTarget = { 0,0,1,0 };
        center_To_camTarget = XMVector3Transform(center_To_camTarget, rotateY);

        // 長さを加える
        float center_To_camTargetDistance = 7.f;
        center_To_camTarget *= center_To_camTargetDistance;

        // 原点からの位置を求めて、カメラの焦点を設定
        XMVECTOR origin_To_camTarget = XMLoadFloat3(&center) + center_To_camTarget;
        XMStoreFloat3(&camTarget, origin_To_camTarget);

        // center_To_camTargetの逆ベクトルを用意
        XMVECTOR center_To_camPosition = -center_To_camTarget;

        // ちょっと回転させる
        float littleAngle = -30.f;
        center_To_camPosition = XMVector3Transform(center_To_camPosition, XMMatrixRotationY(XMConvertToRadians(littleAngle)));

        // 原点からの位置を求めて、カメラの位置を設定
        XMVECTOR origin_To_camPosition = XMLoadFloat3(&center) + center_To_camPosition;
        XMStoreFloat3(&camPosition, origin_To_camPosition);
    }

    // ｘ軸の回転を行う
    {
        // 中心を移動
        XMVECTOR newCenter = (XMLoadFloat3(&camPosition) + XMLoadFloat3(&camTarget)) * 0.5f;
        XMFLOAT3 prevCenter = center;
        XMStoreFloat3(&center, newCenter);

        // 縦回転の軸を作成
        XMVECTOR axis = XMLoadFloat3(&center) - XMLoadFloat3(&prevCenter);

        //// 回転行列を作成
        XMMATRIX rotateAxis = XMMatrixRotationAxis(axis, XMConvertToRadians(angle_.x));

        //　焦点を設定 
        XMVECTOR newCenter_To_camTarget = XMLoadFloat3(&camTarget) - XMLoadFloat3(&center);
        newCenter_To_camTarget = XMVector3Transform(newCenter_To_camTarget, rotateAxis);
        XMVECTOR origin_To_camTarget = XMLoadFloat3(&center) + newCenter_To_camTarget;
        XMStoreFloat3(&camTarget, origin_To_camTarget);

        // 位置を設定
        XMVECTOR newCenter_To_camPosition = -newCenter_To_camTarget;
        XMVECTOR origin_To_camPosition = XMLoadFloat3(&center) + newCenter_To_camPosition;
        XMStoreFloat3(&camPosition, origin_To_camPosition);
    }

    Camera::SetTarget(camTarget);
    Camera::SetPosition(camPosition);
}

void TPSCamera::Draw()
{
}

void TPSCamera::Release()
{
}
