#include "UIButton.h"
#include "../../../Engine/ImGui/imgui.h"

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
	if(loadObj.contains("imageFilePath_"))imageFilePath_ = loadObj["imageFilePath_"].get<string>();
}

void UIButton::DrawData()
{
	ImGui::Text("ImageFilePath");
}
