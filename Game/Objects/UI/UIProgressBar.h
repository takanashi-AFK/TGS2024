#pragma once

#include "UIObject.h"
#include "../../../Engine/Json/JsonReader.h"
#include "../../../Engine/ImGui/imgui.h"
#include <string>
#include <vector>
#include "../../../Game/Objects/Stage/Components/HealthManagerComponents/Component_HealthManager.h" 

class UIProgressBar : public UIObject
{
private:
    float gaugeMaxValue_, gaugeNowValue_, gaugeAnimValue_;
    XMFLOAT3 color_;  // 色を格納するメンバ変数
    std::string imageFilePath_;
    int imageHandle_;
    int pictGaugeHandle_;
    int pictFrameHandle_;
    Transform transGauge_;
    Transform transFrame_;
    Component_HealthManager* healthManager_;  // ポインタ変数を作る

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

    void SetHealthManager(Component_HealthManager* healthManager);  // メンバ関数として追加
    void SetNowBar(float now, float max);  // メンバ関数として追加

    float GetGaugeMaxValue() { return gaugeMaxValue_; }
    float GetGaugeCurrentValue() { return gaugeNowValue_; }
    float GetGaugeAnimValue() { return gaugeAnimValue_; }
};