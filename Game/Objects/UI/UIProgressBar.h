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
    float gaugeMaxValue_, gaugeCurrentValue_, gaugeAnimValue_;
    void SetImage(string _imageFilePath);

    string imageFilePath_;
    int imageHandle_;
    int pictGaugeHandle_;
    int pictFrameHandle_;
    Transform transGauge_;
public:
	UIProgressBar(string _name, GameObject* parent);
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;

	void Save(json& saveObj) override;
	void Load(json& loadObj) override;
	void DrawData() override;

    void SetGaugeMaxValue(float maxValue);
    void SetGaugeCurrentValue(float currentValue);
    void SetGaugeAnimValue();

    // ÉQÉbÉ^Å[
    const std::string& GetFrameImageFileName() const { return frameImageFileName; }
    const std::vector<int>& GetImageNumbers() const { return imageNumbers; }
    float GetGaugeMaxValue() { return gaugeMaxValue_; }
    float GetGaugeCurrentValue() { return gaugeCurrentValue_; }
    float GetGaugeAnimValue() { return gaugeAnimValue_; }

};

