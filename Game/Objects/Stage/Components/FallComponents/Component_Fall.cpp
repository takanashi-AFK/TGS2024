#include "Component_Fall.h"

//インクルード
#include "../../StageObject.h"
#include "../../../../../Engine/ImGui/imgui.h"
// コンストラクタ
Component_Fall::Component_Fall(StageObject* _holder)
    : Component(_holder,"Component_Fall",Fall), fallSpeed_(0.0f), riseSpeed_(0.0f)
{
}

// 初期化
void Component_Fall::Initialize()
{
    // 初期化
    fallSpeed_ = 1.0f; 
    riseSpeed_ = 1.0f; 
}

// 更新
void Component_Fall::Update()
{
    //降下と上昇
    if (holder_->GetPosition().y > 0) {
        holder_->SetPosition(holder_->GetPosition().x, holder_->GetPosition().y - fallSpeed_, holder_->GetPosition().z);
    }
    else {
        holder_->SetPosition(holder_->GetPosition().x, holder_->GetPosition().y + riseSpeed_, holder_->GetPosition().z);
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
    ImGui::SliderFloat("Fall Speed", &fallSpeed_, 0.0f, 10.0f);
    ImGui::SliderFloat("Rise Speed", &riseSpeed_, 0.0f, 10.0f);
}