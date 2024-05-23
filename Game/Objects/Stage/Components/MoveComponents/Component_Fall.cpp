#include "Component_Fall.h"

//インクルード
#include "../../StageObject.h"
#include "../../../../../Engine/ImGui/imgui.h"
// コンストラクタ
Component_Fall::Component_Fall(StageObject* _holder)
    : Component(_holder,"Component_Fall",Fall), fallSpeed_(0), riseSpeed_(0), isRising_(false), tempFallSpeed_(0)
{
}

// 初期化
void Component_Fall::Initialize()
{
    // 初期化
    //fallSpeed_ = 0.5f; 
    //fallSpeedplus_ = 0.05f;
    //riseSpeed_ = 0.05f; 
   
}

// 更新
void Component_Fall::Update()

{   // 現在の位置を取得
    XMFLOAT3 position_ = holder_->GetPosition();


    if (isRising_ == true) {
        // 上昇中の処理
        if (position_.y < 5.0f) { 
            holder_->SetPosition(position_.x, position_.y += riseSpeed_, position_.z);
        }
        else {
            // 物体が一定高さに達したら上昇を停止する
            isRising_ = false;
            fallSpeed_ = tempFallSpeed_;
        }
    }
    else {
        // 降下中の処理
        if (position_.y > -5.0f) {
            //holder_->SetPosition(position_.x, position_.y -= fallSpeed_, position_.z);
            holder_->SetPosition(position_.x, position_.y -= (fallSpeed_ += fallSpeedplus_), position_.z);
        }
        else {
            // 物体が一定の高さに達したら上昇を開始する
            isRising_ = true;
           
        }
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
    if (_loadObj.contains("fallSpeed"))fallSpeed_ = _loadObj["fallSpeed"];
    
    if (_loadObj.contains("riseSpeed"))riseSpeed_ = _loadObj["riseSpeed"];
    
}

// ImGui表示
void Component_Fall::DrawData()
{
    // ImGui描画
    ImGui::Text("Component_Fall");
    ImGui::DragFloat("fallSpeed_", &tempFallSpeed_, 0.1f);

    if (ImGui::Button("fall")) {
        Falling();
    }
    if (ImGui::Button("rise")) {
		Rising();
	}
    //ImGui::SliderFloat("Fall Speed", &fallSpeed_, 0.0f, 10.0f);
    //ImGui::SliderFloat("Rise Speed", &riseSpeed_, 0.0f, 10.0f);
}