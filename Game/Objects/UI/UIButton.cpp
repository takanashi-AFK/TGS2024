#include "UIButton.h"

#include "../../../Engine/ResourceManager/Image.h"
#include "../../../Engine/DirectX/Input.h"
#include "../../../Engine/DirectX/EasingFunction.h"
#include "../../../Engine/ImGui/imgui.h"
#include "../../../Engine/DirectX/Direct3D.h"

using namespace Direct3D;

UIButton::UIButton(GameObject* _parent)
	:UIObject("UIButton", _parent), UIButtonPict_(-1), isButtonPushed_(false)
{
}

void UIButton::Initialize()
{
	//ボタンが押されていない状態にする
	isButtonPushed_ = false;
	//画像の読み込み
	UIButtonPict_ = Image::Load("Assets/Images/TestButton.png");
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
	static int currentEasingFunc = 0;
	for(const auto& pair : EaseFunc)
		easingFunc.push_back(pair.first);

	if(ImGui::BeginCombo("Ease Function", easingFunc[currentEasingFunc].c_str())){
		for(int i = 0; i < easingFunc.size(); i++){
			bool FuncSelected = (currentEasingFunc == i);
			if (ImGui::Selectable(easingFunc[i].c_str(), FuncSelected)) {
								currentEasingFunc = i;
			}
				
		}
		ImGui::EndCombo();
	}

	if (ImGui::Button("Apply Easing")) {
		auto selectedEasingFunc = EaseFunc[easingFunc[currentEasingFunc]];
	}

	// 自身の変形情報を描画
	if (ImGui::TreeNode("transform_")) {
		ImGui::DragFloat3("position_", &transform_.position_.x, 0.1f);
		ImGui::DragFloat3("rotate_", &transform_.rotate_.x, 1.f, -360.f, 360.f);
		ImGui::DragFloat3("scale_", &transform_.scale_.x, 0.1f, 0.f, LONG_MAX);
		ImGui::TreePop();
	}

}

void UIButton::SetPosition(int x, int y) 
{
	transform_.position_.x = (float)(x - Direct3D::screenWidth_ / 2) / Direct3D::screenWidth_;
	transform_.position_.y = (float)(Direct3D::screenHeight_ / 2) / (Direct3D::screenHeight_ / 2);
	center_ = XMFLOAT3(x, y, 0);
}

void UIButton::SetImage()
{
}

bool UIButton::MouseInArea(XMFLOAT3 mousePos)
{
	if (abs(mousePos.x - center_.x) > size_.x / 2 || abs(mousePos.y - center_.y) > size_.y / 2)
		return false;


	return true;
}

bool UIButton::ClickButton()
{
	if (MouseInArea(mousePos_) && Input::IsMouseButtonDown(0)) {
		return true;
	}

	return false;
}
