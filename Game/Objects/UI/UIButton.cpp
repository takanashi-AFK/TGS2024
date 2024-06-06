#include "UIButton.h"
#include "../../../Engine/ResourceManager/Image.h"
#include "../../../Engine/DirectX/Input.h"
#include "../../../Engine/DirectX/EasingFunction.h"

UIButton::UIButton(string _name ,GameObject* _parent)
	:UIObject("UIButton", _parent), UIButtonPict_(-1), isButtonPushed_(false)
{
}

void UIButton::Initialize()
{
	//ボタンが押されていない状態にする
	isButtonPushed_ = false;
	//画像の読み込み
	UIButtonPict_ = Image::Load("Assets/Image/TestButton.png");
	//画像の読み込みに失敗した場合
	assert(UIButtonPict_ >= 0);
	//画像のサイズを取得
	size_ = Image::GetTextureSize(UIButtonPict_);
}

void UIButton::Update() 
{
	DrawGUI();
	//マウスの位置を取得
	mousePos_ = Input::GetMousePosition();
}

void UIButton::Draw()
{
	Image::SetTransform(UIButtonPict_, transform_);
	Image::Draw(UIButtonPict_);
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
	std::vector<std::string> easingFunc;
	static int currentEasing = 0;
	//for(const auto& pair : EaseFunc)
	//	easingFunc.push_back(pair.first);

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
