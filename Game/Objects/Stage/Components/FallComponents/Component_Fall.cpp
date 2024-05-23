#include "Component_Fall.h"

//インクルード
#include "../../StageObject.h"
#include "../../../../../Engine/ImGui/imgui.h"

// コンストラクタ
Component_Fall::Component_Fall(StageObject* _holder)
    : Component(_holder,"Component_Fall",Fall), fallSpeed_(0), riseSpeed_(0), isRising(false)
{
}

// 初期化
void Component_Fall::Initialize()
{
    // 初期化
    fallSpeed_ = 0.5f; 
    fallSpeedplus_ = 0.05f;
    riseSpeed_ = 0.05f; 
   
}

// 更新
void Component_Fall::Update()
{   
    // 現在のローカル位置を取得
    DirectX::XMFLOAT3 localPosition_ = holder_->GetLocalPosition();
    
    if (isRising) {
        // 上昇中の処理
        if (localPosition_.y < 5.0f){
            localPosition_.y += riseSpeed_;
        }
        else{
            // 物体が一定高さに達したら上昇を停止する
            isRising = false;
        }
    }
    else {
        // 降下中の処理
        if (localPosition_.y > -5.0f) {
            localPosition_.y -= (fallSpeed_ += fallSpeedplus_);   
        }
        else {
            // 物体が一定の高さに達したら上昇を開始する
            isRising = true;
            fallSpeed_ = 0.5f; // fallSpeed_をリセット
        }
    }
    // ローカル位置を設定
    holder_->SetLocalPosition(localPosition_.x, localPosition_.y, localPosition_.z);
}

// 開放
void Component_Fall::Release()
{
    
}

// 保存
void Component_Fall::Save(json& _saveObj)
{
    // 保存
    _saveObj["fallSpeed"] = fallSpeed_;
    _saveObj["riseSpeed"] = riseSpeed_;
}

// 読込
void Component_Fall::Load(json& _loadObj)
{
    // 読込
    if (_loadObj.contains("fallSpeed")) {
        fallSpeed_ = _loadObj["fallSpeed"];
    }
    if (_loadObj.contains("riseSpeed")) {
        riseSpeed_ = _loadObj["riseSpeed"];
    }
}

// ImGui表示
void Component_Fall::DrawData()
{
    // ImGui描画
    ImGui::Text("Component_Fall");
    ImGui::DragFloat("fallSpeed_", &fallSpeed_, 0.1f);
    //ImGui::SliderFloat("Fall Speed", &fallSpeed_, 0.0f, 10.0f);
    //ImGui::SliderFloat("Rise Speed", &riseSpeed_, 0.0f, 10.0f);
}