#include "Component_Gauge.h"

// インクルード
#include "../../../../../Engine/ImGui/imgui.h"

Component_Gauge::Component_Gauge(StageObject* _holder, string _name, ComponentType _type, Component* _parent)
	:Component(_holder, _name, _type, _parent), max_(100), now_(100)
{

}

void Component_Gauge::Save(json& _saveObj)
{
	_saveObj["max_"] = max_;
	_saveObj["now_"] = now_;
}

void Component_Gauge::Load(json& _loadObj)
{
	if (_loadObj.contains("max_"))max_ = _loadObj["max_"];
	if (_loadObj.contains("now_"))now_ = _loadObj["now_"];
}

void Component_Gauge::DrawData()
{	
	ImGui::DragFloat("max", &max_, 1.0f);
	ImGui::DragFloat("now", &now_, 1.0f, 0.0f, max_);

	if (ImGui::Button("AdjustToMax"))AdjustToMax();
}

