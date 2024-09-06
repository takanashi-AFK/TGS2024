#pragma once

#include "UIObject.h"
#include "../../../Engine/Json/JsonReader.h"
#include "../../../Engine/ImGui/imgui.h"
#include "../../../Game/Objects/Stage/Components/GaugeComponents/Component_HealthGauge.h"
#include <string>
#include <vector>

using std::string;
using std::vector;

// プログレスバーの画像情報構造体
struct ProgressBarImage{
    string filePath_;       // ファイルパス
    int handle_;            // ハンドル
    Transform transform_;   // 位置、回転、拡大縮小
    XMFLOAT3 color_;        // 色

    bool Load(string _filepath);    // 画像の読み込み
    bool IsAvailable() const;       // 画像が読み込まれているか
};

class UIProgressBar : public UIObject
{
private:
    float* max_;    // 最大値
    float* now_;	    // 現在値

    ProgressBarImage frameImage_;   // フレーム画像
    ProgressBarImage gaugeImage_;   // ゲージ画像
public:
    UIProgressBar(std::string _name, UIObject* parent, int _layerNum);
    void Initialize() override;
    void Update() override;
    void Draw() override;
    void Release() override;

    void Save(json& saveObj) override;
    void Load(json& loadObj) override;
    void DrawData() override;

    void SetMax(float* _max) { max_ = _max; }
    void SetNow(float* _now) { now_ = _now; }
    void SetProgress(float* _now ,float* _max){ now_ = _now; max_ = _max; }

private:
    bool GetImageFilePathFromExplorer(string& _filePath) const;
};