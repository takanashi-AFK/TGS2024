#include "UIButton.h"

#include "../../../Engine/ResourceManager/Image.h"
#include "../../../Engine/DirectX/Input.h"
#include "../../../Engine/DirectX/EasingFunction.h"
#include "../../../Engine/ImGui/imgui.h"
#include "../../../Engine/DirectX/Direct3D.h"

using namespace Direct3D;

UIButton::UIButton(GameObject* _parent)
	:UIObject("UiButton", _parent), UIButtonPict_(-1)
{

}

void UIButton::Initialize()
{
	UIButtonPict_ = Image::Load("Images/TestButton.png");
	assert(UIButtonPict_ >= 0);

	// 画像の大きさを取得
	imagesize_ = Image::GetSize(UIButtonPict_);

	// ウィンドウ上での画像の大きさに変換
	imagesize_.x /= Direct3D::screenWidth_;
	imagesize_.y /= Direct3D::screenHeight_;

}

void UIButton::Update()
{
	// マウスの座標を取得
	XMFLOAT3 mousePos_ = Input::GetMousePosition();

	// マウスの座標を画像の座標に変換
	ConvertToImageCoordinates(mousePos_);
	ImGui::Text("mousePos_ x:%f y:%f", mousePos_.x, mousePos_.y);

	// マウスが画像の領域内に入っているかどうか
	ImGui::Text("isInArea = %s", MouseInArea(mousePos_) ? "true" : "false");

	if (ImGui::TreeNode("transform_")) {
		ImGui::DragFloat3("position_", &transform_.position_.x, 0.1f);
		ImGui::DragFloat3("rotate_", &transform_.rotate_.x, 1.f, -360.f, 360.f);
		ImGui::DragFloat3("scale_", &transform_.scale_.x, 0.1f, 0.f, LONG_MAX);
		ImGui::TreePop();
	}

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

bool UIButton::MouseInArea(XMFLOAT3 mousePos)
{
	XMFLOAT2 center = { transform_.position_.x,transform_.position_.y };

	float scaleX = transform_.scale_.x;
	float scaleY = transform_.scale_.y;

	float top = center.y - (imagesize_.y * scaleY) ;
	float bottom = center.y + (imagesize_.y * scaleY);
	float left = center.x - (imagesize_.x * scaleX) ;
	float right = center.x + (imagesize_.x  * scaleX);

	// 判定範囲内にマウスカーソルが入っているかどうかを返す
	return (mousePos.x >= left && mousePos.x <= right && mousePos.y >= top && mousePos.y <= bottom);
}

bool UIButton::ClickButton()
{
	// マウスの座標を取得
	XMFLOAT3 mousePos = Input::GetMousePosition();

	// マウスの座標を画像の座標に変換
	ConvertToImageCoordinates(mousePos);

	//マウスのポジションが画像の領域に入っているかつ左クリックが押されたら
	return MouseInArea(mousePos) && Input::IsMouseButtonDown(0);
}

void UIButton::ConvertToImageCoordinates(XMFLOAT3& _position)
{
	int scWidth = Direct3D::screenWidth_;
	int scHeight = Direct3D::screenHeight_;

#ifdef _DEBUG
	scWidth = scWidth * 0.7;
	scHeight = scHeight * 0.7;
#endif // _DEBUG

	// マウスの座標を画像の座標に変換
	_position.x = (float)(_position.x * 2.0f) / (float)scWidth - 1.0f;
	_position.y = 1.0f - (float)(_position.y * 2.0f) / (float)scHeight;

	ImGui::Text("mousePos_ x:%f y:%f", _position.x, _position.y);
	ImGui::Text("screenWidth_:%d screenHeight_:%d", scWidth, scHeight);
}

void UIButton::DrawGui()
{
	std::vector<std::string> easingFunc;
	static int currentEasingFunc = 0;
	for (const auto& pair : EaseFunc)
		easingFunc.push_back(pair.first);

	if (ImGui::BeginCombo("Ease Function", easingFunc[currentEasingFunc].c_str())) {
		for (int i = 0; i < easingFunc.size(); i++) {
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
	

}



