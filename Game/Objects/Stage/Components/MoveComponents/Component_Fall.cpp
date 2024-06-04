#include "Component_Fall.h"

// インクルード
#include "../../../../../Engine/ImGui/imgui.h"
#include "../../StageObject.h"

// コンストラクタ
Component_Fall::Component_Fall(string _name, StageObject* _holder, Component* _parent)
	: Component(_holder,_name,Fall,_parent)
	, fallSpeed_(), riseSpeed_(),fallDistance_(),
	isFalling_(false), isFirstTime_(true), isActive_(false), startRisePosition_(), startFallPosition_()
{
}

// 初期化
void Component_Fall::Initialize()
{
}

// 更新
void Component_Fall::Update()
{   
	// 実行したかどうか
	if (isActive_) {

		XMFLOAT3 pPos = holder_->GetPosition();
		if (isFirstTime_) {
			// 下降・上昇の開始位置を保持する変数
			startRisePosition_.y = pPos.y;
			startFallPosition_.y = pPos.y;

			isFirstTime_ = false;
		}

		if (isFalling_) {
			// 降下中の処理
			if (pPos.y > startFallPosition_.y - fallDistance_) {
				pPos.y -= fallSpeed_;
			}
			else {
				// 物体が一定の高さに達したら上昇を開始する
				isFalling_ = false;
				pPos.y = startFallPosition_.y - fallDistance_;
			}
		}
		else {
			
			// 上昇中の処理
			if (pPos.y < startRisePosition_.y) {
				pPos.y += riseSpeed_;
			}
			else {
				// 物体が一定高さに達したら上昇を停止し、降下を開始する
				isFalling_ = true;
				isActive_ = false;
				isFirstTime_ = true;
				pPos.y = startRisePosition_.y;  // 上昇開始位置に戻す
				startFallPosition_.y = pPos.y;  // 降下開始位置を記録
			}
		}
		// 位置を確定
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
	_saveObj["fallSpeed_"] = fallSpeed_;
	_saveObj["riseSpeed_"] = riseSpeed_;
	_saveObj["fallDistance_"] = fallDistance_;
}

// 読込
void Component_Fall::Load(json& _loadObj)
{
	// 読込
	if (_loadObj.contains("fallSpeed_"))fallSpeed_ = _loadObj["fallSpeed_"];
	if (_loadObj.contains("riseSpeed_"))riseSpeed_ = _loadObj["riseSpeed_"];
	if (_loadObj.contains("fallDistance_"))fallDistance_ = _loadObj["fallDistance_"];
}

// ImGui表示
void Component_Fall::DrawData()
{
	// ImGui描画
	ImGui::Text("Component_Fall");
	ImGui::DragFloat("fallSpeed_", &fallSpeed_, 0.1f);
	ImGui::DragFloat("riseSpeed_", &riseSpeed_, 0.1f);
	ImGui::DragFloat("fallDistance_", &fallDistance_, 0.1f);
	if (ImGui::Button("Execute"))Execute();
	
}
