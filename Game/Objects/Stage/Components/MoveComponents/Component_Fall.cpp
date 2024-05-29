#include "Component_Fall.h"

// インクルード
#include "../../../../../Engine/ImGui/imgui.h"
#include "../../StageObject.h"


// コンストラクタ
Component_Fall::Component_Fall(StageObject* _holder)
    : Component(_holder,"Component_Fall",Fall)
	, fallSpeed_(0.5f), fallSpeedplus_(0.05f), riseSpeed_(0.05f),fallDistance_(5.0f),
	isRising_(false), isFirstTime_(true)
{
}

// 初期化
void Component_Fall::Initialize()
{
    
}

// 更新
void Component_Fall::Update()
{   
	if (isActive_) {

		XMFLOAT3 pPos = holder_->GetPosition();
		if (isFirstTime_) {
			// 下降・上昇の開始位置を保持する変数
			startRisePosition_.y = pPos.y;
			startFallPosition_.y = pPos.y;

			isFirstTime_ = false;
		}

		if (isRising_) {
			// 上昇中の処理
			if (pPos.y < startRisePosition_.y) {
				pPos.y += riseSpeed_;
			}
			else {
				// 物体が一定高さに達したら上昇を停止し、降下を開始する
				isRising_ = false;
				isActive_ = false;
				isFirstTime_ = true;
				pPos.y = startRisePosition_.y;  // 上昇開始位置に戻す
				startFallPosition_.y = pPos.y;  // 降下開始位置を記録
			}
		}
		else {
			// 降下中の処理
			if (pPos.y > startFallPosition_.y - fallDistance_) {
				pPos.y -= (fallSpeed_ + fallSpeedplus_);
			}
			else {
				// 物体が一定の高さに達したら上昇を開始する
				isRising_ = true;
				pPos.y = startFallPosition_.y - fallDistance_;
			}
		}

		holder_->SetPosition(pPos);

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
    ImGui::DragFloat("fallSpeed_", &fallSpeed_, 0.1f);
	ImGui::DragFloat("fallSpeedPuls_", &fallSpeedplus_, 0.1f);
	ImGui::DragFloat("riseSpeed_", &riseSpeed_, 0.1f);
	ImGui::DragFloat("fallDistance_", &fallDistance_, 0.1f);
    if (ImGui::Button("Falling")) {
        Execute();
    }
    //ImGui::SliderFloat("Fall Speed", &fallSpeed_, 0.0f, 10.0f);
    //ImGui::SliderFloat("Rise Speed", &riseSpeed_, 0.0f, 10.0f);
}
