#include "UIProgressBar.h"
#include "../../../Engine/ImGui/imgui.h"
#include "../../../Engine/Global.h"
#include "../../../Engine/ResourceManager/Image.h"

UIProgressBar::UIProgressBar(string _name, GameObject* parent)
    : UIObject(_name, UIType::UI_PROGRESSBAR, parent)
{
}

void UIProgressBar::Initialize()
{
     pictGaugeHandle_= Image::Load("Images/HPBar.png");
        assert(pictGaugeHandle_ >= 0);
}

void UIProgressBar::Update()
{
}

void UIProgressBar::Draw()
{
    // 画像が読み込まれていない場合は処理を行わない
    if (imageHandle_ < 0)return;

    Transform transGauge = transform_;
    transGauge.scale_.x = (float)gaugeAnimValue_/ (float)gaugeMaxValue_;

    Image::SetTransform(pictGaugeHandle_, transGauge);
    Image::Draw(pictGaugeHandle_);

    Image::SetTransform(imageHandle_, transform_);
    Image::Draw(imageHandle_);

}

void UIProgressBar::Release()
{
}

void UIProgressBar::Save(json& saveObj) {
    saveObj["imageFilePath_"] = imageFilePath_;
    saveObj["gaugeMaxValue_"] = gaugeMaxValue_;
    saveObj["gaugeCurrentValue_"] = gaugeCurrentValue_;
}

void UIProgressBar::Load(json& loadObj) {
    if (loadObj.contains("imageFilePath_")) {
        imageFilePath_ = loadObj["imageFilePath_"].get<string>();
        SetImage(imageFilePath_);
    }
    gaugeMaxValue_ = loadObj["gaugeMaxValue"].get<float>();
    gaugeCurrentValue_ = loadObj["gaugeCurrentValue"].get<float>();
}

void UIProgressBar::DrawData() {
    if (ImGui::TreeNode("imageFilePath_")) {

        ImGui::Text("imageFilePath_:%s", imageFilePath_.c_str());
        ImGui::SameLine();

        if (ImGui::SmallButton("...")) {
            //現在のカレントディレクトリを覚えておく
            char defaultCurrentDir[MAX_PATH];
            GetCurrentDirectory(MAX_PATH, defaultCurrentDir);

            // 追加するオブジェクトのモデルファイルパスを設定
            {
                // 「ファイルを開く」ダイアログの設定用構造体を設定
                OPENFILENAME ofn; {
                    TCHAR szFile[MAX_PATH] = {}; // ファイル名を格納するバッファ
                    ZeroMemory(&ofn, sizeof(ofn)); // 構造体の初期化
                    ofn.lStructSize = sizeof(ofn); // 構造体のサイズ
                    ofn.lpstrFile = szFile; // ファイル名を格納するバッファ
                    ofn.lpstrFile[0] = '\0'; // 初期化
                    ofn.nMaxFile = sizeof(szFile); // ファイル名バッファのサイズ
                    ofn.lpstrFilter = TEXT("PNGファイル(*.fbx)\0*.png\0すべてのファイル(*.*)\0*.*\0"); // フィルター（FBXファイルのみ表示）
                    ofn.nFilterIndex = 1; // 初期選択するフィルター
                    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST; // フラグ（ファイルが存在すること、パスが存在することを確認）
                    ofn.lpstrInitialDir = TEXT("."); // カレントディレクトリを初期選択位置として設定
                }

                // ファイルを選択するダイアログの表示
                if (GetOpenFileName(&ofn) == TRUE) {
                    // ファイルパスを取得
                    imageFilePath_ = ofn.lpstrFile;

                    // カレントディレクトリからの相対パスを取得
                    imageFilePath_ = FileManager::GetAssetsRelativePath(imageFilePath_);

                    // 文字列内の"\\"を"/"に置換
                    FileManager::ReplaceBackslashes(imageFilePath_);

                    // ディレクトリを戻す
                    SetCurrentDirectory(defaultCurrentDir);

                    // 画像を読み込む
                    SetImage(imageFilePath_);
                }
                else {
                    return;
                }
            }
        }
        ImGui::TreePop();
    }

    // ゲージの現在値と最大値を設定できるようにする
    ImGui::SliderFloat("Current Value", &gaugeCurrentValue_, 0.0f, gaugeMaxValue_);
    ImGui::SliderFloat("Max Value", &gaugeMaxValue_, 0.0f, 200.0f);  // 最大値の上限は適宜変更

    // ゲージの現在値をプログレスバーとして表示
    ImGui::ProgressBar(gaugeCurrentValue_ / gaugeMaxValue_, ImVec2(0.0f, 0.0f));

}

void UIProgressBar::SetImage(string _imageFilePath)
{
    imageFilePath_ = _imageFilePath;
    imageHandle_ = Image::Load(_imageFilePath);
}

void UIProgressBar::SetGaugeMaxValue(float maxValue) {
    gaugeMaxValue_ = maxValue;
}

void UIProgressBar::SetGaugeCurrentValue(float currentValue) {
    gaugeCurrentValue_ = currentValue;
}

void UIProgressBar::SetGaugeAnimValue()
{
    gaugeAnimValue_ = (gaugeAnimValue_ * 9 + gaugeCurrentValue_) / 10;
}
