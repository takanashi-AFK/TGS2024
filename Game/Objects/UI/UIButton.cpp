#include "UIButton.h"

#include "../../../Engine/ResourceManager/Image.h"
#include "../../../Engine/ImGui/imgui.h"

UIButton::UIButton(string _name ,GameObject* _parent)
	:UIObject("UIButton", _parent), UIButtonPict_(-1)
{
}

void UIButton::Initialize()
{

}

void UIButton::Update() 
{

}

void UIButton::Draw()
{

}

void UIButton::Release()
{

}

void UIButton::Save(json& _saveUIobj)
{
}

void UIButton::Load(json& _loadUIobj)
{
}

void UIButton::DrawGUI()
{
}

void UIButton::SetImage()
{
}

bool UIButton::MouseInArea(XMFLOAT3 mousePos)
{
	return false;
}

void UIButton::ClickButton(bool pushed)
{
}
