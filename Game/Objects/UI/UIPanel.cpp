#include "UIPanel.h"

UIPanel::UIPanel(string _name,GameObject* _parent) 
	: UIObject(_name, _parent)
{
}

void UIPanel::Initialize()
{
}

void UIPanel::Update()
{
}

void UIPanel::Draw()
{
}

void UIPanel::Release()
{
}

void UIPanel::Save(json& _saveUiobj)
{
}
	
void UIPanel::Load(json& _loadUiobj)
{
}

void UIPanel::AddChild(UIObject* _child)
{
}

void UIPanel::RemoveChild(UIObject* _child)
{
}

void UIPanel::ClearChild()
{
}





