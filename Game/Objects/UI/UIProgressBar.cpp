#include "UIProgressBar.h"
#include "../../../Engine/ImGui/imgui.h"
#include "../../../Engine/Global.h"
#include "../../../Engine/ResourceManager/Image.h"
#include "../../../Engine/DirectX/Direct3D.h"
#include "../Stage/Stage.h"
#include "../../../Game/Objects/Stage/StageObject.h"
#include "../../../Game/Objects/Stage/Components/Component.h"


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
  //参照しているコンポーネントがあるかどうか
  //  if (referenceGauge_.this_ == nullptr)
		//// これが悪い なんでrefereceGaugeがnullなのにreferenceGaugeのholderName_を？
  //      referenceGauge_.this_ = (Component_Gauge*)((StageObject*)FindObject(referenceGauge_.holderName_))->FindComponent(referenceGauge_.thisName_);
    if(referenceGauge_.this_ == nullptr)return;
    //参照するゲージコンポーネントから値を取得
    if (referenceGauge_.this_ != nullptr) {
        gaugeMaxValue_ = referenceGauge_.this_->GetMax();
        gaugeNowValue_ = referenceGauge_.this_->GetNow();
    }
    
}

void UIProgressBar::Draw()
{
    if (imageHandle_ < 0) return;
    
   // 設定された値から変形行列`transform_`の値を計算
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
    if (target_ != nullptr)saveObj["target_"] = target_->GetObjectName();
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
    if (loadObj.contains("target_"))targetName_ = loadObj["target_"];
    gaugeMaxValue_ = loadObj["gaugeMaxValue_"].get<float>();
    gaugeNowValue_ = loadObj["gaugeNowValue_"].get<float>();
    color_ = { loadObj["color_"][0].get<float>(),loadObj["color_"][1].get<float>(), loadObj["color_"][2].get<float>() };
}

void UIProgressBar::DrawData()
{
    // ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
    // プログレスバーのフレーム画像を設定
    // ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
    if (ImGui::TreeNode("imageFilePath_")) {

        // 現在のファイルパスを表示
        ImGui::Text("imageFilePath_:%s", imageFilePath_.c_str());
        ImGui::SameLine();

        // ファイルパスを取得
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
                ImGui::TreePop();
            }
        }
        ImGui::TreePop();
    }


    // ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
    // ゲージ表示色を設定
    // ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
    ImVec4 inputCol = { REFERENCE_XMFLOAT3(color_),0 };
    ImGui::ColorEdit4("Color", (float*)&inputCol);
    color_ = {REFERENCE_XMFLOAT3(inputCol)};

// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// ゲージコンポーネント情報を取得
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
 // ゲージコンポーネント情報を取得
    vector<gauge> gauges;

    // ステージ情報を取得
    vector<StageObject*> objects = ((Stage*)FindObject("Stage"))->GetStageObjects();

    //ステージ内のオブジェクトを参照してすべてのゲージコンポーネントを取得
    for (auto obj : objects) {
        //HPゲージを探して取得
        for (auto healthGaugeComp : obj->FindComponent(HealthGauge)) {
            //配列にオブジェクトとコンポーネントを一つにまとめて入れる？
            auto gaugeComp = dynamic_cast<Component_Gauge*>(healthGaugeComp);
            gauges.push_back({ obj,gaugeComp,obj->GetObjectName(),gaugeComp->GetName() });
        }
        //技ゲージ...
    }
    static int select = 0;

    if (gauges.empty())return;
    //コンボボックスでgaugeのコンテナにあるselect番目のコンポーネントを文字列に変換して受け取る？
    if (ImGui::BeginCombo("gauge_", gauges[select].thisName_.c_str())) {
        for (int i = 0; i < gauges.size(); i++) {
            //selectが現在のインデックスiと等しいかどうかをチェック。
            bool is_selected = (select == i);
            //is_selectedがtrueなら要素名を表示する
            if (ImGui::Selectable(gauges[i].thisName_.c_str(), is_selected))
                select = i;
            if (is_selected)
                //選択されたアイテムにフォーカスをセット
                ImGui::SetItemDefaultFocus();
        }
        ImGui::EndCombo();
    }


    //メンバ変数の struct gauge referenceGauge_に選択されたゲージを設定
    referenceGauge_ = gauges[select];

    gaugeMaxValue_ = referenceGauge_.this_->GetMax();
    gaugeNowValue_ = referenceGauge_.this_->GetNow();

    ImGui::Text("%f,%f", gaugeMaxValue_, gaugeNowValue_);


    //vector<gauge> gauges;

    //// ステージ情報を取得
    //vector<StageObject*> objects = ((Stage*)FindObject("Stage"))->GetStageObjects();

    ////ステージ内のオブジェクトを参照してすべてのゲージコンポーネントを取得
    //for (auto obj : objects) {
    //    //HPゲージを探して取得
    //    for (auto healthGaugeComp : obj->FindComponent(HealthGauge)) {
    //        //配列にオブジェクトとコンポーネントを一つにまとめて入れる？
    //        auto gaugeComp = dynamic_cast<Component_Gauge*>(healthGaugeComp);
    //        gauges.push_back({ obj,gaugeComp,obj->GetObjectName(),gaugeComp->GetName() });
    //    }
    //    //技ゲージ...
    //}
    //static int select = 0;

    //if (gauges.empty())return;
    ////コンボボックスでgaugeのコンテナにあるselect番目のコンポーネントを文字列に変換して受け取る？
    //if (ImGui::BeginCombo("gauge_", gauges[select].thisName_.c_str())) {
    //    for (int i = 0; i < gauges.size(); i++) {
    //        //selectが現在のインデックスiと等しいかどうかをチェック。
    //        bool is_selected = (select == i);
    //        //is_selectedがtrueなら要素名を表示する
    //        if (ImGui::Selectable(gauges[select].thisName_.c_str(), is_selected))
    //            select = i;
    //        if (is_selected)
    //            //選択されたアイテムにフォーカスをセット
    //            ImGui::SetItemDefaultFocus();
    //    }
    //    ImGui::EndCombo();
    //}


    ////メンバ変数の struct gauge referenceGauge_に選択されたゲージを設定
    //referenceGauge_ = gauges[select];

    //gaugeMaxValue_ = referenceGauge_.this_->GetMax();
    //gaugeNowValue_ = referenceGauge_.this_->GetNow();

    //ImGui::Text("%f,%f", gaugeMaxValue_, gaugeNowValue_);

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

