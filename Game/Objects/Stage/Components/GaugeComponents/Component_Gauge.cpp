#include "Component_Gauge.h"

// インクルード
#include "../../../../../Engine/ImGui/imgui.h"

Component_Gauge::Component_Gauge(StageObject* _holder, string _name, ComponentType _type, Component* _parent)
	:Component(_holder, _name, _type, _parent), maxGauge_(0), nowGauge_(0)
{

}

