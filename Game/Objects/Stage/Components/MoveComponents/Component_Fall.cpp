#include "Component_Fall.h"

// インクルード
#include "../../../../../Engine/ImGui/imgui.h"

#include "../../StageObject.h"
#include "../TimerComponent/Component_Timer.h"

namespace
{
	float riseWaitTime_ = 5 ;			//上昇
	float fallWaitTime_ = 0.8;			//降下
}

// コンストラクタ
Component_Fall::Component_Fall(string _name, StageObject* _holder, Component* _parent)
	: Component(_holder, _name, Fall, _parent)
	, fallSpeed_(), riseSpeed_(), fallDistance_(),
	isFalling_(false), isFirstTime_(true), isActive_(false), startRisePosition_(), startFallPosition_(), state_(WAIT), prevState_(RISE)
{
}

// 初期化
void Component_Fall::Initialize()
{
	if (FindChildComponent("Timer") == false)AddChildComponent(CreateComponent("Timer", Timer, holder_, this));
}

// 更新
void Component_Fall::Update()
{   
	// 実行したかどうか
	if (isActive_) {
		XMFLOAT3 holderPos = holder_->GetPosition();
		auto timer = dynamic_cast<Component_Timer*>(GetChildComponent("Timer"));
		if (timer == nullptr) return;
		if (isFirstTime_) {
			// 下降・上昇の開始位置を保持する変数
			startRisePosition_.y = holderPos.y;
			startFallPosition_.y = holderPos.y;

			isFirstTime_ = false;
			isRised_ = false;
		}

		switch (state_)
		{
		case FALL:
			// 降下中の処理
			if (holderPos.y > startFallPosition_.y - fallDistance_) {
				holderPos.y -= (fallSpeed_ );
				isFalling_ = true;
			}
			else {
				// 物体が一定の高さに達したら上昇を開始する
				timer->Reset();
				holderPos.y = startFallPosition_.y - fallDistance_;
				prevState_ = FALL;
				state_ = WAIT;
			}
			break;

		case RISE:
			// 上昇中の処理
			if (holderPos.y < startRisePosition_.y) {
				holderPos.y += riseSpeed_;
				isFalling_ = false;
			}
			else {
				// 物体が一定高さに達したら上昇を停止し、降下を開始する
				timer->Reset();
				prevState_ = RISE;
				state_ = WAIT;
				isActive_ = false;
				isFirstTime_ = true;
				holderPos.y = startRisePosition_.y;  // 上昇開始位置に戻す
				startFallPosition_.y = holderPos.y;  // 降下開始位置を記録
			}
			break;

		case WAIT:
			isFalling_ = false;
			if (prevState_ == FALL) {
				timer->SetTime(riseWaitTime_);
				timer->Start();
				if (timer->GetIsEnd()) {
					state_ = RISE;
				}
			}
			else if (prevState_ == RISE) {
				timer->SetTime(fallWaitTime_);
				timer->Start();
				if (timer->GetIsEnd()) {
					state_ = FALL;
				}
			}
			ImGui::Text("Time:%f", timer->GetNowTime());

			break;

		}

		// 位置を確定
		holder_->SetPosition(holderPos);
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
	_saveObj["riseWaitTime_"] = riseWaitTime_;
	_saveObj["fallWaitTime_"] = fallWaitTime_;
}

// 読込
void Component_Fall::Load(json& _loadObj)
{
	// 読込
	if (_loadObj.contains("fallSpeed_"))fallSpeed_ = _loadObj["fallSpeed_"];
	if (_loadObj.contains("riseSpeed_"))riseSpeed_ = _loadObj["riseSpeed_"];
	if (_loadObj.contains("fallDistance_"))fallDistance_ = _loadObj["fallDistance_"];
	if (_loadObj.contains("riseWaitTime_"))riseWaitTime_ = _loadObj["riseWaitTime_"];
	if (_loadObj.contains("fallWaitTime_"))fallWaitTime_ = _loadObj["fallWaitTime_"];
}

// ImGui表示
void Component_Fall::DrawData()
{
	// ImGui描画
	ImGui::Text("Component_Fall");
	ImGui::DragFloat("fallSpeed_", &fallSpeed_, 0.1f);
	ImGui::DragFloat("riseSpeed_", &riseSpeed_, 0.1f);
	ImGui::DragFloat("fallDistance_", &fallDistance_, 0.1f);
	ImGui::DragFloat("riseWaitTime_", &riseWaitTime_, 0.1f);
	ImGui::DragFloat("fallWaitTime_", &fallWaitTime_, 0.1f);

	if (ImGui::Button("Falling")) {
		Start();
	}
}
