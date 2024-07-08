#include "TPSCamera.h"
#include "../../../Engine/DirectX/Input.h"
#include "../../../Engine/GameObject/Camera.h"
#include "../Stage/Stage.h"
#include "../Stage/StageObject.h"
#include "../../../Engine/ImGui/imgui.h"


namespace {
    const float DEF_SENSITIVITY = 0.3f;
    const float SENSITIVITY_MAX = 1;
    const float SENSITIVITY_MIN = 0;
}


TPSCamera::TPSCamera(GameObject* parent)
	:GameObject(parent, "TPSCamera"), angle_({ 0,0 }), sensitivity_(DEF_SENSITIVITY), pTarget_(nullptr), isActive_(true), targetHeight_(4.f), targetDistance_(7.f), prevAxis_({ 1,0,0,0 })
{
}

void TPSCamera::Initialize()
{
}

void TPSCamera::Update()
{
	if (isActive_ == false)return;

    if (pTarget_ == nullptr) pTarget_ = FindObject(targetName_);
    if (pTarget_ == nullptr) return;

    // カメラの焦点・位置を格納する変数を用意
    XMFLOAT3 camTarget{};
    XMFLOAT3 camPosition{};

    // 回転の中心を設定１⃣
    XMFLOAT3 center = pTarget_->GetPosition();
    center.y += targetHeight_;

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
        float center_To_camTargetDistance = targetDistance_;
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

        if (XMVector3Equal(axis, XMVectorZero())) {
            axis = prevAxis_;
        }

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

        if(!XMVector3Equal(axis, XMVectorZero()))
        prevAxis_ = axis;
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

void TPSCamera::DrawData()
{
	// カメラの有効無効 //////////////////////////////////////////////
	ImGui::Checkbox("isActive", &isActive_);


	// カメラの感度 //////////////////////////////////////////////
	ImGui::DragFloat("sensitivity", &sensitivity_, 0.1f,SENSITIVITY_MIN, SENSITIVITY_MAX);


	// カメラの高さ //////////////////////////////////////////////
	ImGui::DragFloat("targetHeight", &targetHeight_,0.1f);


	// カメラの距離 //////////////////////////////////////////////
	ImGui::DragFloat("targetDistance", &targetDistance_, 0.1f);


	// 対象の選択 //////////////////////////////////////////////
    std::vector<string> objNames;
    objNames.push_back("null");

    for (auto obj : (((Stage*)FindObject("Stage"))->GetStageObjects()))
        objNames.push_back(obj->GetObjectName());

    static int select = 0;

    if (select >= objNames.size())return;

    if (ImGui::BeginCombo("target_", objNames[select].c_str())) {
        for (int i = 0; i < objNames.size(); i++) {
            bool is_selected = (select == i);
            if (ImGui::Selectable(objNames[i].c_str(), is_selected))select = i;
            if (is_selected)ImGui::SetItemDefaultFocus();
        }
        ImGui::EndCombo();
    }

    targetName_ = objNames[select];
}

void TPSCamera::Save(json& saveObj)
{
	saveObj["isActive_"] = isActive_;
	saveObj["sensitivity_"] = sensitivity_;
	saveObj["targetHeight_"] = targetHeight_;
	saveObj["targetDistance_"] = targetDistance_;
	saveObj["targetName_"] = targetName_;
}

void TPSCamera::Load(json& loadObj)
{
	if (loadObj.contains("isActive_"))isActive_ = loadObj["isActive_"];
	if (loadObj.contains("sensitivity_"))sensitivity_ = loadObj["sensitivity_"];
	if (loadObj.contains("targetHeight_"))targetHeight_ = loadObj["targetHeight_"];
	if (loadObj.contains("targetDistance_"))targetDistance_ = loadObj["targetDistance_"];
	if (loadObj.contains("targetName_"))targetName_ = loadObj["targetName_"];
}
