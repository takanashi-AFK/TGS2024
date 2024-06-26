#pragma once

#include "UIObject.h"
#include "../../../Engine/Json/JsonReader.h"
#include <string>
#include <vector>
class UIProgressBar : public UIObject
{
private:
    std::string frameImageFileName;
    std::vector<int> imageNumbers;
    int gaugeColorRed, gaugeColorGreen, gaugeColorBlue;
    float gaugeMaxValue, gaugeCurrentValue;
    void SetImage(string _imageFilePath);

    string imageFilePath_;
    int imageHandle_;

public:
	UIProgressBar(string _name, GameObject* parent);
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;

	void Save(json& saveObj) override;
	void Load(json& loadObj) override;
	void DrawData() override;

    // セッター
    void SetFrameImageFileName(const std::string& fileName);
    void SetGaugeColor(int r, int g, int b);
    void SetGaugeMaxValue(float maxValue);
    void SetGaugeCurrentValue(float currentValue);

    // ゲッター
    const std::string& GetFrameImageFileName() const { return frameImageFileName; }
    const std::vector<int>& GetImageNumbers() const { return imageNumbers; }
    int GetGaugeRed() const { return gaugeColorRed; }
    int GetGaugeGreen() const { return gaugeColorGreen; }
    int GetGaugeBlue() const { return gaugeColorBlue; }
    float GetGaugeMaxValue() const { return gaugeMaxValue; }
    float GetGaugeCurrentValue() const { return gaugeCurrentValue; }

    

};

