#include "Component_Gauge.h"

// インクルード
#include "../../../../../Engine/ImGui/imgui.h"

Component_Gauge::Component_Gauge(string _name, StageObject* _holder, ComponentType _type, Component* _parent)
	:Component(_holder, _name, _type, _parent), maxGauge_(0), nowGauge_(0)
{

}

void Component_Gauge::Initialize()
{
}

void Component_Gauge::Update()
{
}

void Component_Gauge::Release()
{
}

void Component_Gauge::Save(json& _saveObj)
{
	_saveObj["maxGauge_"] = maxGauge_;
	_saveObj["nowGauge_"] = nowGauge_;
}

void Component_Gauge::Load(json& _loadObj)
{
	if (_loadObj.contains("maxGauge_"))maxGauge_ = _loadObj["maxGauge_"];
	if (_loadObj.contains("nowGauge_"))nowGauge_ = _loadObj["nowGauge_"];
}

void Component_Gauge::DrawData()
{
	ImGui::DragFloat("MaxHP", &maxGauge_, 1.0f);
	ImGui::DragFloat("HP", &nowGauge_, 1.0f, 0.0f, maxGauge_);

	if (ImGui::Button("Reset"))Reset();
}

float Component_Gauge::GetGauge() const
{
	return nowGauge_;
}

void Component_Gauge::SetGauge(float _newGauge)
{
	if (_newGauge <= maxGauge_)nowGauge_ = _newGauge;
}

float Component_Gauge::GetMax() const
{
	return maxGauge_;
}

void Component_Gauge::SetMax(float _newMaxGauge)
{
	maxGauge_ = _newMaxGauge;
}

void Component_Gauge::Reset()
{
	nowGauge_ = maxGauge_;
}