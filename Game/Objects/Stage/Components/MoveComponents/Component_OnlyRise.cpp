#include "Component_OnlyRise.h"
#include "../../../../../Engine/ImGui/imgui.h"
#include "../../StageObject.h"
Component_OnlyRise::Component_OnlyRise(string _name, StageObject* _holder, Component* _parent) :
	Component(_holder, _name, ComponentType::OnlyRise, _parent)
{
}

void Component_OnlyRise::Initialize()
{
}

void Component_OnlyRise::Update()
{
	if (isActive_) {

		// 高さが目標の高さに達していなかったら...
		if (height_ < targetHeight_) {

			// 上昇速度分だけ高さを上げる
			height_ += riseSpeed_;

		}
		else {
			// 目標の高さに設定
			height_ = targetHeight_;
			isActive_ = false;
		}
		holder_->SetPosition(holder_->GetPosition().x, height_, holder_->GetPosition().z);
	}
}

void Component_OnlyRise::Release()
{
}

void Component_OnlyRise::Save(json& _saveObj)
{
	_saveObj["riseSpeed_"] = riseSpeed_;
	_saveObj["height_"] = height_;
	_saveObj["targetHeight_"] = targetHeight_;
}

void Component_OnlyRise::Load(json& _loadObj)
{
	if (_loadObj.contains("riseSpeed_"))riseSpeed_ = _loadObj["riseSpeed_"];
	if (_loadObj.contains("height_"))height_ = _loadObj["height_"];
	if (_loadObj.contains("targetHeight_"))targetHeight_ = _loadObj["targetHeight_"];
}

void Component_OnlyRise::DrawData()
{
	ImGui::DragFloat("riseSpeed_", &riseSpeed_, 0.1f);
	ImGui::DragFloat("targetHeight_", &targetHeight_, 0.1f);

	if (ImGui::Button("Rising"))Execute();
}
