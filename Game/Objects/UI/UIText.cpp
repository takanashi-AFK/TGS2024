#include "UIText.h"
#include "../../../Engine/ResourceManager/Text.h"
#include "../../../Engine/ImGui/imgui.h"
#include "../../../Engine/DirectX/Direct3D.h"

UIText::UIText(string _name, GameObject* parent)
	: UIObject(_name, UI_TEXT, parent), pText_(nullptr), drawText_(""), size_(1.f), floatNum_(nullptr)
{
}

void UIText::Initialize()
{
	// テキストオブジェクトを生成＆初期化
	pText_ = new Text;
	pText_->Initialize();

	LockScale();
	LockRotate();

}

void UIText::Update()
{
}

void UIText::Draw()
{
	// 表示サイズを計算
	pText_->SetScale(size_);

	// 表示位置を計算
	float drawX = (transform_.position_.x * (Direct3D::screenWidth_ / 2)) + (Direct3D::screenWidth_ / 2);		
	float drawY = (transform_.position_.y * (Direct3D::screenHeight_ / 2)) + (Direct3D::screenHeight_ / 2);
	
	// テキストを描画
	if (floatNum_ == nullptr)pText_->Draw(drawX, drawY, drawText_.c_str());
	else pText_->Draw(drawX, drawY,*floatNum_);
}

void UIText::Release()
{
	// テキストオブジェクトの解放
	pText_->Release();
}

void UIText::Save(json& saveObj)
{
	saveObj["text"] = drawText_;
	saveObj["size"] = size_;
}

void UIText::Load(json& loadObj)
{
	if (loadObj.contains("text"))drawText_ = loadObj["text"].get<string>();
	if (loadObj.contains("size"))size_ = loadObj["size"].get<float>();
}

void UIText::DrawData()
{
	// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	// 表示するテキストを変更
	// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	if(floatNum_ == nullptr)
	if (ImGui::TreeNode("TextString")) {
		ImGui::Text("Current Text : %s", drawText_.c_str());
		char buffer[256] = "";
		if (ImGui::InputTextWithHint("##Input", "Input New Text...", buffer, IM_ARRAYSIZE(buffer)))
			this->drawText_ = buffer;
		ImGui::TreePop();
	}

	// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	// フォントサイズを変更
	// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	ImGui::DragFloat("size", &size_, 0.01f);
}
