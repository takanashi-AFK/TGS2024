#include "Component_HelingoFall.h"

// インクルード
#include "../../../../../Engine/ImGui/imgui.h"

#include "../../StageObject.h"
#include "../TimerComponent/Component_Timer.h"
#include "../MoveComponents/Component_Fall.h"
#include "../MoveComponents/Component_Rise.h"


namespace
{
	float riseWaitTime_ = 5 ;			//上昇
	float fallWaitTime_ = 0.8;			//降下
}

// コンストラクタ
Component_HelingoFall::Component_HelingoFall(string _name, StageObject* _holder, Component* _parent)
	: Component(_holder, _name, Fall, _parent),
	fallSpeed_(), riseSpeed_(), fallDistance_(),startHeight_(),
	isActive_(false), nowState_(WAIT), prevState_(RISE)
{
}

// 初期化
void Component_HelingoFall::Initialize()
{
	if (FindChildComponent("Timer") == false)AddChildComponent(CreateComponent("Timer", Timer, holder_, this));
	if (FindChildComponent("OnlyFall") == false)AddChildComponent(CreateComponent("OnlyFall", OnlyFall, holder_, this));
	if (FindChildComponent("OnlyRise") == false)AddChildComponent(CreateComponent("OnlyRise", OnlyRise, holder_, this));
}

// 更新
void Component_HelingoFall::Update()
{   
	auto fall = dynamic_cast<Component_Fall*>(GetChildComponent("OnlyFall"));
	if (fall == nullptr) return;

	auto rise = dynamic_cast<Component_Rise*>(GetChildComponent("OnlyRise"));
	if (rise == nullptr) return;

	// 実行したかどうか
	if (isActive_) {
		XMFLOAT3 holderPos = holder_->GetPosition();
		
		switch (nowState_)
		{
		case FALL:
			fall->Execute(); 
			if (fall->IsActive()) {
				auto timer = dynamic_cast<Component_Timer*>(GetChildComponent("Timer"));
				timer->Reset();
				SetState(WAIT);
			}
			break;	// 降下中の処理

		case RISE:
			rise->Execute();
			if (rise->IsEnd()) {
				auto timer = dynamic_cast<Component_Timer*>(GetChildComponent("Timer"));
				timer->Reset();
				Stop();
				SetState(WAIT);
			}
			break;	// 上昇中の処理
		case WAIT:
			Wait();				 break;	// 待機中の処理
		}

		// 位置を確定
		holder_->SetPosition(holderPos);
	}
}

// 開放
void Component_HelingoFall::Release()
{
}

// 保存
void Component_HelingoFall::Save(json& _saveObj)
{
	// 保存
	_saveObj["fallSpeed_"] = fallSpeed_;
	_saveObj["riseSpeed_"] = riseSpeed_;
	_saveObj["fallDistance_"] = fallDistance_;
	_saveObj["riseWaitTime_"] = riseWaitTime_;
	_saveObj["fallWaitTime_"] = fallWaitTime_;
}

// 読込
void Component_HelingoFall::Load(json& _loadObj)
{
	// 読込
	if (_loadObj.contains("fallSpeed_"))fallSpeed_ = _loadObj["fallSpeed_"];
	if (_loadObj.contains("riseSpeed_"))riseSpeed_ = _loadObj["riseSpeed_"];
	if (_loadObj.contains("fallDistance_"))fallDistance_ = _loadObj["fallDistance_"];
	if (_loadObj.contains("riseWaitTime_"))riseWaitTime_ = _loadObj["riseWaitTime_"];
	if (_loadObj.contains("fallWaitTime_"))fallWaitTime_ = _loadObj["fallWaitTime_"];
}

// ImGui表示
void Component_HelingoFall::DrawData()
{
	// ImGui描画
	ImGui::Text("Component_Fall");
	ImGui::Text(nowState_ == FALL ? "FALL" : nowState_ == RISE ? "RISE" : "WAIT");
	ImGui::Text(prevState_ == FALL ? "FALL" : prevState_ == RISE ? "RISE" : "WAIT");
	ImGui::Text("isActive_ : %s", isActive_ ? "true" : "false");

	ImGui::DragFloat("riseWaitTime_", &riseWaitTime_, 0.1f);
	ImGui::DragFloat("fallWaitTime_", &fallWaitTime_, 0.1f);

	if (ImGui::Button("Falling")) {
		Execute();
	}
}

void Component_HelingoFall::FallMove(float& _height)
{
	// 前回の状態が待機状態の時、開始の高さを記録
	// 2週目でこのifに入らないようにするため、prevStateをFALLに変更
	if (prevState_ == WAIT) {
		startHeight_ = _height;
		prevState_ = FALL;
	}
	// 目標の高さ
	float  targetHeight = startHeight_ - fallDistance_;
	
	// 高さが目標の高さに達していなかったら...
	if (_height > targetHeight) {
		
		// 降下速度分だけ高さを下げる
		_height -= (fallSpeed_);

	}
	// 高さが一定の高さに達したら...
	else {
		// タイマーをリセット
		auto timer = dynamic_cast<Component_Timer*>(GetChildComponent("Timer"));
		timer->Reset();

		// 目標の高さに設定
		_height = targetHeight;
		
		// 待機状態に遷移
		SetState(WAIT);
	}
}

void Component_HelingoFall::RiseMove(float& _height)
{
	// 目標の高さ
	float targetHeight = startHeight_;

	// 高さが目標の高さに達していなかったら...
	if (_height < targetHeight) {

		// 上昇速度分だけ高さを上げる
		_height += riseSpeed_;

	}
	else {
		// タイマーをリセット
		auto timer = dynamic_cast<Component_Timer*>(GetChildComponent("Timer"));
		timer->Reset();

		// 目標の高さに設定
		_height = targetHeight;

		// 待機状態に遷移
		SetState(WAIT);

		// 動作を終了
		Stop();
	}
}

void Component_HelingoFall::Wait()
{
	// タイマーを取得
	auto timer = dynamic_cast<Component_Timer*>(GetChildComponent("Timer"));
	
	if (prevState_ == FALL) {

		// タイマーを開始
		timer->SetTime(riseWaitTime_);
		timer->Start();

		auto rise = dynamic_cast<Component_Rise*>(GetChildComponent("OnlyRise"));
		if (rise == nullptr) return;
		rise->SetIsEnd(false);

		// タイマーが終了したら、上昇状態に遷移
		if(timer->GetIsEnd())SetState(RISE);
	}

	else if (prevState_ == RISE) {

		// タイマーを開始
		timer->SetTime(fallWaitTime_);
		timer->Start();

		// タイマーが終了したら、降下状態に遷移
		if (timer->GetIsEnd())SetState(FALL);
	}

	float time = timer->GetNowTime();
	ImGui::Text("time : %f", time);
}
