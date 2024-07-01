#include "UIProgressBar.h"
#include "../../../Engine/ImGui/imgui.h"
#include "../../../Engine/Global.h"
#include "../../../Engine/ResourceManager/Image.h"
#include "../../../Engine/DirectX/Direct3D.h"

UIProgressBar::UIProgressBar(string _name, GameObject* parent)
	:UIObject(_name, UIType::UI_PROGRESSBAR, parent),
    gaugeMaxValue_(100.0f),  // 初期値を設定
    gaugeNowValue_(50.0f),  // 初期値を設定
    gaugeAnimValue_(0.0f),  // 初期値を設定
    color_(1.0f, 1.0f, 1.0f) // 初期化: 白色
{
}

void UIProgressBar::Initialize()
{
    pictGaugeHandle_ = Image::Load("Images/Bar_Gauge.png");
    assert(pictGaugeHandle_ >= 0);

    pictFrameHandle_ = Image::Load("Images/Bar_Frame.png");
    assert(pictFrameHandle_ >= 0);
}

void UIProgressBar::Update()
{
}

void UIProgressBar::Draw()
{
    if (imageHandle_ < 0) return;
    
    // ゲージのスケールを計算
    transGauge_ = transform_;
    transGauge_.scale_.x = (gaugeNowValue_ / gaugeMaxValue_) * transFrame_.scale_.x;

    // ゲージの画像を描画
    Image::SetTransform(pictGaugeHandle_, transGauge_);
    Image::Draw(pictGaugeHandle_,Direct3D::SHADER_BAR,color_);
    
    transFrame_ = transform_;

    Image::SetTransform(pictFrameHandle_, transFrame_);
    Image::Draw(pictFrameHandle_);
}

void UIProgressBar::Release()
{
}

void UIProgressBar::Save(json& saveObj)
{
    saveObj["imageFilePath_"] = imageFilePath_;
    saveObj["gaugeMaxValue_"] = gaugeMaxValue_;
    saveObj["gaugeNowValue_"] = gaugeNowValue_;
    saveObj["color_"] = { REFERENCE_XMFLOAT3(color_) };
}

void UIProgressBar::Load(json& loadObj)
{
    if (loadObj.contains("imageFilePath_")) {
        imageFilePath_ = loadObj["imageFilePath_"].get<string>();
        SetImage(imageFilePath_);
    }
    gaugeMaxValue_ = loadObj["gaugeMaxValue_"].get<float>();
    gaugeNowValue_ = loadObj["gaugeNowValue_"].get<float>();
    color_ = { loadObj["color_"][0].get<float>(),loadObj["color_"][1].get<float>(), loadObj["color_"][2].get<float>() };
}

void UIProgressBar::DrawData()
{
    if (ImGui::TreeNode("imageFilePath_")) {
        ImGui::Text("imageFilePath_:%s", imageFilePath_.c_str());
        ImGui::SameLine();

        if (ImGui::SmallButton("...")) {
            // 現在のカレントディレクトリを覚えておく
            char defaultCurrentDir[MAX_PATH];
            GetCurrentDirectory(MAX_PATH, defaultCurrentDir);

            // 「ファイルを開く」ダイアログの設定
            OPENFILENAME ofn; {
                TCHAR szFile[MAX_PATH] = {};
                ZeroMemory(&ofn, sizeof(ofn));
                ofn.lStructSize = sizeof(ofn);
                ofn.lpstrFile = szFile;
                ofn.lpstrFile[0] = '\0';
                ofn.nMaxFile = sizeof(szFile);
                ofn.lpstrFilter = TEXT("PNGファイル(*.fbx)\0*.png\0すべてのファイル(*.*)\0*.*\0");
                ofn.nFilterIndex = 1;
                ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
                ofn.lpstrInitialDir = TEXT(".");
            }

            // ファイル選択ダイアログの表示
            if (GetOpenFileName(&ofn) == TRUE) {
                // ファイルパスを取得
                imageFilePath_ = ofn.lpstrFile;
                imageFilePath_ = FileManager::GetAssetsRelativePath(imageFilePath_);
                FileManager::ReplaceBackslashes(imageFilePath_);
                SetCurrentDirectory(defaultCurrentDir);
                SetImage(imageFilePath_);
            }
            else {
                return;
            }
        }
        ImGui::TreePop();
    }
    // カラー・ピッカー
    ImVec4 temp = {color_.x,color_.y,color_.z,0};
    ImGui::ColorEdit4("Color", (float*)&temp);
    color_ = { temp.x,temp.y,temp.z };

    // ゲージの制御
    ImGui::SliderFloat("Current Value", &gaugeNowValue_, 0.0f, gaugeMaxValue_);
    ImGui::SliderFloat("Max Value", &gaugeMaxValue_, 0.0f, 200.0f);
    ImGui::ProgressBar(gaugeNowValue_ / gaugeMaxValue_, ImVec2(0.0f, 0.0f));

}


void UIProgressBar::SetImage(string _imageFilePath)
{
    imageFilePath_ = _imageFilePath;
    pictFrameHandle_ = Image::Load(_imageFilePath);
}

void UIProgressBar::SetGaugeMaxValue(float maxValue)
{
    gaugeMaxValue_ = maxValue;
}

void UIProgressBar::SetGaugeCurrentValue(float currentValue) {
    gaugeNowValue_ = currentValue;
}

void UIProgressBar::SetGaugeAnimValue()
{
    // アニメーション値を現在値に近づける
    gaugeAnimValue_ = (gaugeAnimValue_ * 9 + gaugeNowValue_) / 10.0f;
}