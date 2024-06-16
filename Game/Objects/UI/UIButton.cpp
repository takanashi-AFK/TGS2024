#include "UIButton.h"

UIButton::UIButton(string _name, GameObject* parent)
	: UIObject(_name, UIType::UI_BUTTON, parent)
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

void UIButton::Save(json& saveObj)
{
	saveObj["imageFilePath_"] = imageFilePath_;
}

void UIButton::Load(json& loadObj)
{
}

void UIButton::DrawData()
{
}
