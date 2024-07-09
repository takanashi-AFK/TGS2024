#pragma once

#include "UIObject.h"
#include "../../../Engine/Json/JsonReader.h"
#include "../../../Engine/ImGui/imgui.h"
#include "../../../Game/Objects/Stage/Components/GaugeComponents/Component_HealthGauge.h"
#include <string>
#include <vector>

struct gauge {
    StageObject* holder_;
    Component_Gauge* this_;
    string holderName_;
    string thisName_;
};

class UIProgressBar : public UIObject
{
private:
    float gaugeMaxValue_, gaugeNowValue_;
    XMFLOAT3 color_;  // 色を格納するメンバ変数
    std::string imageFilePath_;
    int imageHandle_;
    int pictGaugeHandle_;
    int pictFrameHandle_;
    Transform transGauge_;
    Transform transFrame_;
    Component_HealthGauge* healthGauge_; // HealthGaugeのポインタを追加
    StageObject* target_;
    string targetName_;

    gauge referenceGauge_;
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

    void SetGaugeMaxValue(float _maxValue);
    void SetGaugeCurrentValue(float _nowValue);
   
    void SetGauge(Component_HealthGauge* _gauge) { healthGauge_ = _gauge; }

    float GetGaugeMaxValue() { return gaugeMaxValue_; }
    float GetGaugeCurrentValue() { return gaugeNowValue_; }
    
    void SetColor(XMFLOAT3 _col) { color_ = _col; }
    void SetColor(float _r, float _g, float _b) { SetColor(XMFLOAT3(_r, _g, _b)); }
};