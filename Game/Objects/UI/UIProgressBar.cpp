#include "UIProgressBar.h"
#include "../../../Engine/ImGui/imgui.h"

UIProgressBar::UIProgressBar(string _name, GameObject* parent)
	: UIObject(_name, UIType::UI_PROGRESSBAR, parent)
{
}

void UIProgressBar::Initialize()
{
}

void UIProgressBar::Update()
{
}

void UIProgressBar::Draw()
{
}

void UIProgressBar::Release()
{
}

void UIProgressBar::Save(json& saveObj) {
    saveObj["frameImageFileName"] = frameImageFileName;
    saveObj["gaugeColorRed"] = gaugeColorRed;
    saveObj["gaugeColorGreen"] = gaugeColorGreen;
    saveObj["gaugeColorBlue"] = gaugeColorBlue;
    saveObj["gaugeMaxValue"] = gaugeMaxValue;
    saveObj["gaugeCurrentValue"] = gaugeCurrentValue;
}

void UIProgressBar::Load(json& loadObj) {
    frameImageFileName = loadObj["frameImageFileName"].get<std::string>();
    gaugeColorRed = loadObj["gaugeColorRed"].get<int>();
    gaugeColorGreen = loadObj["gaugeColorGreen"].get<int>();
    gaugeColorBlue = loadObj["gaugeColorBlue"].get<int>();
    gaugeMaxValue = loadObj["gaugeMaxValue"].get<float>();
    gaugeCurrentValue = loadObj["gaugeCurrentValue"].get<float>();
}

void UIProgressBar::DrawData() {
    ImGui::Text("Progress Bar Settings");

    // フレーム画像のファイル名を入力できるようにする
    static char frameImageFileNameBuffer[256];
    strcpy(frameImageFileNameBuffer, frameImageFileName.c_str());
    if (ImGui::InputText("Frame Image File Name", frameImageFileNameBuffer, sizeof(frameImageFileNameBuffer))) {
        frameImageFileName = std::string(frameImageFileNameBuffer);
    }

    // ゲージの色を選択できるようにする
    float color[3] = { gaugeColorRed / 255.0f, gaugeColorGreen / 255.0f, gaugeColorBlue / 255.0f };
    if (ImGui::ColorEdit3("Gauge Color", color)) {
        gaugeColorRed = static_cast<int>(color[0] * 255);
        gaugeColorGreen = static_cast<int>(color[1] * 255);
        gaugeColorBlue = static_cast<int>(color[2] * 255);
    }

    // ゲージの現在値と最大値を設定できるようにする
    ImGui::SliderFloat("Current Value", &gaugeCurrentValue, 0.0f, gaugeMaxValue);
    ImGui::SliderFloat("Max Value", &gaugeMaxValue, 0.0f, 1000.0f);  // 最大値の上限は適宜変更

    // ゲージの現在値をプログレスバーとして表示
    ImGui::ProgressBar(gaugeCurrentValue / gaugeMaxValue, ImVec2(0.0f, 0.0f));
}

void UIProgressBar::SetFrameImageFileName(const std::string& fileName) {
    frameImageFileName = fileName;
}

void UIProgressBar::SetGaugeColor(int r, int g, int b) {
    gaugeColorRed = r;
    gaugeColorGreen = g;
    gaugeColorBlue = b;
}

void UIProgressBar::SetGaugeMaxValue(float maxValue) {
    gaugeMaxValue = maxValue;
}

void UIProgressBar::SetGaugeCurrentValue(float currentValue) {
    gaugeCurrentValue = currentValue;
}
