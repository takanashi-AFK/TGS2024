#include "UITimer.h"


UITimer::UITimer(string _name, UIObject* parent, int _layerNum)
	: UIObject(_name, UI_TIMER, parent, _layerNum)
{
}

void UITimer::Initialize()
{
}

void UITimer::Update()
{
}

void UITimer::Draw()
{
}

void UITimer::Release()
{
}

void UITimer::Save(json& saveObj)
{
}

void UITimer::Load(json& loadObj)
{
}
