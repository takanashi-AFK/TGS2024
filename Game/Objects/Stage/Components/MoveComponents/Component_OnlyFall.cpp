#include "Component_OnlyFall.h"
#include "../../StageObject.h"
#include "../../Components/TimerComponent/Component_Timer.h"
#include "../../../../../Engine/ImGui/imgui.h"
Component_OnlyFall::Component_OnlyFall(string _name, StageObject* _holder, Component* _parent)
	: Component(_holder, _name, OnlyFall, _parent), isActive_(false), fallSpeed_(0.1f), height_(0.0f), startHeight_(0.0f)
{
}

void Component_OnlyFall::Initialize()
{
}

void Component_OnlyFall::Update()
{
	if (isActive_) {

		height_ = holder_->GetPosition().y;
		// 目標の高さ

		// 高さが目標の高さに達していなかったら...
		if (height_ > targetHeight_ || isInfinity_) {

			// 降下速度分だけ高さを下げる
			height_ -= fallSpeed_;

		}
		// 高さが一定の高さに達したら...
		else {
			
			// 目標の高さに設定
			height_ = targetHeight_;
			isActive_ = false;
		}
		holder_->SetPosition(holder_->GetPosition().x,height_,holder_->GetPosition().z);
	}
}

void Component_OnlyFall::Release()
{
}

void Component_OnlyFall::Save(json& _saveObj)
{
	_saveObj["startHeight_"] = startHeight_;
	_saveObj["fallSpeed_"] = fallSpeed_;
	_saveObj["height_"] = height_;
	_saveObj["targetHeight_"] = targetHeight_;

}

void Component_OnlyFall::Load(json& _loadObj)
{
	if (_loadObj.contains("startHeight_"))startHeight_ = _loadObj["startHeight_"];
	if (_loadObj.contains("fallSpeed_"))fallSpeed_ = _loadObj["fallSpeed_"];
	if (_loadObj.contains("height_"))height_ = _loadObj["height_"];
	if (_loadObj.contains("targetHeight_"))targetHeight_ = _loadObj["targetHeight_"];
}

void Component_OnlyFall::DrawData()
{
	ImGui::Checkbox("Is Infinity", &isInfinity_);
	ImGui::DragFloat("Fall Speed", &fallSpeed_, 0.1f, 0.0f, 100.0f);
	ImGui::DragFloat("targetHeight_", &targetHeight_, 0.1f, 0.0f, 100.0f);
	if (ImGui::Button("Execute"))Execute();
	if (ImGui::Button("Stop"))Stop();
	ImGui::Text("height_ : %f", height_);

}
