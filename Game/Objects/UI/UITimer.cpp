#include "UITimer.h"
#include "../../../Engine/ImGui/imgui.h"


UITimer::UITimer(string _name, UIObject* parent, int _layerNum)
	: UIObject(_name, UI_TIMER, parent, _layerNum), max_(0), count_(0), isActive_(false)
{
}

void UITimer::Initialize()
{
}

void UITimer::Update()
{
	// カウンターを更新
	if(isActive_)count_--;

	// カウンターが0になったら非アクティブにする
	if (count_ <= 0){
		count_ = 0;
		isActive_ = false;
	}
}

void UITimer::Draw()
{
}

void UITimer::Release()
{
}

void UITimer::Save(json& saveObj)
{
	// 最大値の保存
	saveObj["max"] = max_;
}

void UITimer::Load(json& loadObj)
{
	// 最大値の読み込み
	max_ = loadObj["max"];
	count_ = max_;
}

void UITimer::DrawData()
{
	// 最大値の設定
	ImGui::DragFloat("max", &max_, 1.f, 1.f, 1000.f);
}
