#include "UITimer.h"

// インクルード
#include "../../../Engine/ImGui/imgui.h"
#include "../../../Engine/ResourceManager/Text.h"


UITimer::UITimer(string _name, UIObject* parent, int _layerNum)
	: UIObject(_name, UI_TIMER, parent, _layerNum), max_(0), count_(0), isActive_(false), pText_(nullptr), size_(1.f)
{
}

void UITimer::Initialize()
{
	// テキストオブジェクトを生成＆初期化
	pText_ = new Text();
	pText_->Initialize();
}

void UITimer::Update()
{
	// カウンターを更新
	if(isActive_)count_--;

	// カウンターが0になったら終了
	if (count_ <= 0) EndTimer();
}

void UITimer::Draw()
{

	// 表示位置を計算
	float drawX = (transform_.position_.x * (Direct3D::screenWidth_ / 2)) + (Direct3D::screenWidth_ / 2);
	float drawY = (transform_.position_.y * (Direct3D::screenHeight_ / 2)) + (Direct3D::screenHeight_ / 2);
	
	// 表示サイズを設定
	pText_->SetScale(size_);

	// 文字列を設定
	string str{}; {
		int totalSeconds = count_ / FPS;
		int minutes = totalSeconds / 60;
		int seconds = totalSeconds % 60;

		str = std::to_string(minutes) + ":" + (seconds < 10 ? "0" : "") + std::to_string(seconds);
	}

	// テキストを描画
	pText_->Draw(drawX, drawY,str.c_str());
}

void UITimer::Release()
{
}

void UITimer::Save(json& saveObj)
{
	// 最大値の保存
	saveObj["max"] = max_;

	// テキストサイズの保存
	saveObj["size"] = size_;
}

void UITimer::Load(json& loadObj)
{
	// 最大値の読み込み
	if(loadObj.contains("max"))max_ = loadObj["max"];
	count_ = max_;

	// テキストサイズの読み込み
	if(loadObj.contains("size"))size_ = loadObj["size"];
}

void UITimer::DrawData()
{
	// 描画の設定
	if (ImGui::TreeNode("draw")) {
		
		// テキストの設定
		ImGui::DragFloat("size", &size_, 0.01f, 0.1f, 10.f);

		
		ImGui::TreePop();
	}

	// 値の設定
	if (ImGui::TreeNode("value")) {

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
