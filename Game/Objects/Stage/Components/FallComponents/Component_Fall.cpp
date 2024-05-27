#include "Component_Fall.h"

// インクルード
#include "../../StageObject.h"
#include "../../../../../Engine/ImGui/imgui.h"


// コンストラクタ
Component_Fall::Component_Fall(StageObject* _holder)
    : Component(_holder,"Component_Fall",Fall), fallSpeed_(0), riseSpeed_(0), isRising_(false),isFirstTime_(true)
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
   
    if (isFirstTime_) {
        
        // 現在のローカル位置を取得
        localPosition = holder_->GetLocalPosition();

        // 下降・上昇の開始位置を保持する変数
        startRisePosition_.y = localPosition.y;
        startFallPosition_.y = localPosition.y;
        
        isFirstTime_ = false;
    }
    if (isActive_) {
        if (isRising_) {
            // 上昇中の処理
            if (localPosition.y < startRisePosition_.y) {
                localPosition.y += riseSpeed_;
                
            }
            else {
                // 物体が一定高さに達したら上昇を停止し、降下を開始する
                isRising_ = false;
                isActive_ = false;
                startFallPosition_.y = localPosition.y;  // 降下開始位置を記録
                fallSpeed_ = 0.5f;  // 降下速度を初期化
            }
        }
        else {
            // 降下中の処理
            if (localPosition.y > startFallPosition_.y - 5.0f) {
                localPosition.y -= (fallSpeed_ += fallSpeedplus_);
            }
            else {
                // 物体が一定の高さに達したら上昇を開始する
                isRising_ = true;
                //startRisePosition_.y = localPosition.y;  // 上昇開始位置を記録
            }
        }
        // ローカル位置を設定
        holder_->SetLocalPosition(localPosition.x, localPosition.y, localPosition.z);
        holder_->SetPosition(localPosition);
        
    }
    
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
    if (ImGui::Button("Falling")) {
        Execute();
    }
    //ImGui::SliderFloat("Fall Speed", &fallSpeed_, 0.0f, 10.0f);
    //ImGui::SliderFloat("Rise Speed", &riseSpeed_, 0.0f, 10.0f);
}
