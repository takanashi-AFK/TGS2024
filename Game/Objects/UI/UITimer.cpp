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
	// カウンターの実行テスト
	if (ImGui::TreeNode("UITimer")) {

		// 開始ボタンの表示
		if(ImGui::SmallButton("start"))StartTimer();
		ImGui::SameLine();

		// 停止ボタンの表示
		if(ImGui::SmallButton("stop"))StopTimer();
		ImGui::SameLine();

		// 終了ボタンの表示
		if(ImGui::SmallButton("end"))EndTimer();
		ImGui::SameLine();
		
		// リセットボタンの表示
		if(ImGui::SmallButton("reset"))ResetTimer();
		ImGui::SameLine();

		// リスタートボタンの表示
		if(ImGui::SmallButton("restart"))RestartTimer();

		// 最大値を秒で設定
		{
			static float sec = 0;
			ImGui::InputFloat("sec", &sec);
			ImGui::SameLine();
			if (ImGui::SmallButton("set"))SetTimer(sec);
		}

		// カウンターの表示
		ImGui::Text("count : %f", count_);
		ImGui::Text("sec   : %f", count_ / FPS);
		ImGui::TreePop();
	}
}
