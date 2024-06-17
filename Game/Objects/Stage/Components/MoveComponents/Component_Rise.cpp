#include "Component_Rise.h"
#include "../../../../../Engine/ImGui/imgui.h"
#include "../../StageObject.h"
#include "../TimerComponent/Component_Timer.h"
Component_Rise::Component_Rise(string _name, StageObject* _holder, Component* _parent) :
	Component(_holder, _name, ComponentType::OnlyRise, _parent),
	riseSpeed_(0.1f),
	height_(0.0f),
	targetHeight_(2.0f),
	isInfinity_(false),
	isEnd_(false)
{
}

void Component_Rise::Initialize()
{
}

void Component_Rise::Update()
{
	if (isActive_) {

		if (isFirst_) {
			height_ = holder_->GetPosition().y;
			isFirst_ = false;
			isEnd_ = false;
		}

		// 高さが目標の高さに達していなかったら...
		if (height_ < targetHeight_ || isInfinity_) {

			// 上昇速度分だけ高さを上げる
			height_ += riseSpeed_;
		}
		else {
			// 目標の高さに設定
			height_ = targetHeight_;
			isFirst_ = true;
			isEnd_ = true;
			Stop();
		}
		holder_->SetPosition(holder_->GetPosition().x, height_, holder_->GetPosition().z);
	}

	ImGui::Text(isEnd_ ? "isEnd_ = true" : "isEnd_ = false");

	ImGui::Text(isFirst_ ? "isFirst_ = First" : "isFirst_ = Not First");
}

void Component_Rise::Release()
{
}

void Component_Rise::Save(json& _saveObj)
{
	_saveObj["riseSpeed_"] = riseSpeed_;
	_saveObj["height_"] = height_;
	_saveObj["targetHeight_"] = targetHeight_;
	_saveObj["isInfinity_"] = isInfinity_;
}

void Component_Rise::Load(json& _loadObj)
{
	if (_loadObj.contains("riseSpeed_"))riseSpeed_ = _loadObj["riseSpeed_"];
	if (_loadObj.contains("height_"))height_ = _loadObj["height_"];
	if (_loadObj.contains("targetHeight_"))targetHeight_ = _loadObj["targetHeight_"];
	if (_loadObj.contains("isInfinity_"))isInfinity_ = _loadObj["isInfinity_"];
}

void Component_Rise::DrawData()
{
	ImGui::Checkbox("isInfinity_", &isInfinity_);
	ImGui::DragFloat("riseSpeed_", &riseSpeed_, 0.1f);
	ImGui::DragFloat("targetHeight_", &targetHeight_, 0.1f);

	if (ImGui::Button("Rising"))Execute();
	if (ImGui::Button("Stop"))Stop();

	ImGui::Text("height_ : %f", height_);
	ImGui::Text(isActive_ ? "Rising" : "Stop");
	
}
