#pragma once

#include "UIObject.h"
#include "../../../Engine/Json/JsonReader.h"
#include "../../../Engine/ImGui/imgui.h"
#include <string>
#include <vector>


class UIProgressBar : public UIObject
{
private:
    float gaugeMaxValue_, gaugeNowValue_, gaugeAnimValue_;
    XMFLOAT3 color_;  // F‚ğŠi”[‚·‚éƒƒ“ƒo•Ï”
    std::string imageFilePath_;
    int imageHandle_;
    int pictGaugeHandle_;
    int pictFrameHandle_;
    Transform transGauge_;
    Transform transFrame_;


public:
    UIProgressBar(std::string _name, GameObject* parent);
    void Initialize() override;
    void Update() override;
    void Draw() override;
    void Release() override;

    void Save(json& saveObj) override;
    void Load(json& loadObj) override;
    void DrawData() override;

    void SetImage(std::string _imageFilePath);

    void SetGaugeMaxValue(float maxValue);
    void SetGaugeCurrentValue(float currentValue);
    void SetGaugeAnimValue();

    float GetGaugeMaxValue() { return gaugeMaxValue_; }
    float GetGaugeCurrentValue() { return gaugeNowValue_; }
    float GetGaugeAnimValue() { return gaugeAnimValue_; }
};