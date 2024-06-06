#include "UIButton.h"
#include "../../../Engine/ResourceManager/Image.h"

UIButton::UIButton(string _name ,GameObject* _parent)
	:UIObject("UIButton", _parent), UIButtonPict_(-1), isButtonPushed_(false)
{
}

void UIButton::Initialize()
{
	isButtonPushed_ = false;
	UIButtonPict_ = Image::Load("Assets/Image/TestButton.png");
	assert(UIButtonPict_ >= 0);
	//size_ = Image::GetSize(UIButtonPict_);
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

void UIButton::ClickButton()
{
}
