#include "UIText.h"
#include "../../../Engine/ResourceManager/Text.h"
#include "../../../Engine/ImGui/imgui.h"

UIText::UIText(string _name, GameObject* parent)
	: UIObject(_name, UI_TEXT, parent), pText_(nullptr), drawText_("")
{
}

void UIText::Initialize()
{
	// テキストオブジェクトを生成＆初期化
	pText_ = new Text;
	pText_->Initialize();
}

void UIText::Update()
{
}

void UIText::Draw()
{
	// テキスト描画
	pText_->Draw(30,30,drawText_.c_str()) ;
}

void UIText::Release()
{
	// テキストオブジェクトの解放
	pText_->Release();
}

void UIText::Save(json& saveObj)
{
}

void UIText::Load(json& loadObj)
{
}

void UIText::DrawData()
{
	// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	// 表示するテキストを変更
	// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	/*if (ImGui::TreeNode("name")) {
		ImGui::Text("Current Text : %s", drawText_.c_str());
		char buffer[256] = "";
		if (ImGui::InputTextWithHint("##Input", "Input New name...", buffer, IM_ARRAYSIZE(buffer)))
			this->objectName_ = buffer;
		ImGui::TreePop();
	}*/
}
