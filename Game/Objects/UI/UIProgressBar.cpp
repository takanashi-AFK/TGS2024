#include "UIProgressBar.h"
#include "../../../Engine/ImGui/imgui.h"
#include "../../../Engine/Global.h"
#include "../../../Engine/ResourceManager/Image.h"
#include "../../../Engine/DirectX/Direct3D.h"
#include "../Stage/Stage.h"
#include "../../../Game/Objects/Stage/StageObject.h"


UIProgressBar::UIProgressBar(string _name, GameObject* parent)
	:UIObject(_name, UIType::UI_PROGRESSBAR, parent),
    gaugeMaxValue_(100.0f),  // 初期値を設定
    gaugeNowValue_(50.0f)  // 初期値を設定
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

    if (healthGauge_ != nullptr) {
        gaugeMaxValue_ = healthGauge_->GetMax();
        gaugeNowValue_ = healthGauge_->GetHP();
    }

    // 設定された値から変形行列`transform_`の値を計算
    // ゲージのスケールを計算
    transGauge_ = transform_;
    transGauge_.scale_.x = (gaugeNowValue_ / gaugeMaxValue_) * transFrame_.scale_.x;

}

void UIProgressBar::Draw()
{
    if (imageHandle_ < 0) return;
    
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

 
   
    //// Stage内に存在するGaugeコンポーネント継承したコンポーネントを全て取得
    //vector<string> objNames;
    //objNames.push_back("null");
    //auto stage = (Stage*)FindObject("Stage");
    //if (stage) {
    //    for (auto obj : stage->GetStageObjects()) {
    //        for (auto component : obj->FindComponent()) {
    //            if (dynamic_cast<Component_Gauge*>(component)) {
    //                objNames.push_back(obj->GetObjectName());
    //                break; // 1オブジェクトに1つのGaugeコンポーネントのみ
    //            }
    //        }
    //    }
    //}

    //static int select = 0;
    //if (ImGui::BeginCombo("Target Gauge", objNames[select].c_str())) {
    //    for (int i = 0; i < objNames.size(); i++) {
    //        bool is_selected = (select == i);
    //        if (ImGui::Selectable(objNames[i].c_str(), is_selected)) select = i;
    //        if (is_selected) ImGui::SetItemDefaultFocus();
    //    }
    //    ImGui::EndCombo();
    //}

    //if (select == 0) {
    //    healthGauge_ = nullptr;
    //}
    //else {
    //    auto selectedObj = stage->FindObject(objNames[select]);
    //    if (selectedObj) {
    //        for (auto component : selectedObj->GetComponents()) {
    //            if (auto gauge = dynamic_cast<Component_Gauge*>(component)) {
    //                healthGauge_ = gauge;
    //                break;
    //            }
    //        }
    //    }
    //}
    
    // ゲージの制御
    ImGui::DragFloat("Current Value", &gaugeNowValue_, 1.f, gaugeMaxValue_);
    ImGui::DragFloat("Max Value", &gaugeMaxValue_, 1.f);
    ImGui::ProgressBar(gaugeNowValue_ / gaugeMaxValue_, ImVec2(0.0f, 0.0f));

}


void UIProgressBar::SetImage(string _imageFilePath)
{
    imageFilePath_ = _imageFilePath;
    pictFrameHandle_ = Image::Load(_imageFilePath);
}

void UIProgressBar::SetGaugeMaxValue(float _maxValue)
{
    gaugeMaxValue_ = _maxValue;
}

void UIProgressBar::SetGaugeCurrentValue(float _nowValue) {
    gaugeNowValue_ = _nowValue;
}

