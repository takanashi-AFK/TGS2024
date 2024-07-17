
#include "UIProgressBar.h"
#include "../../../Engine/ImGui/imgui.h"
#include "../../../Engine/Global.h"
#include "../../../Engine/ResourceManager/Image.h"
#include "../../../Engine/DirectX/Direct3D.h"
#include "../Stage/Stage.h"
#include "../../../Game/Objects/Stage/StageObject.h"
#include "../../../Game/Objects/Stage/Components/Component.h"


UIProgressBar::UIProgressBar(string _name, UIObject* parent,int _layerNum)
    :UIObject(_name, UIType::UI_PROGRESSBAR, parent, _layerNum)
{
}

void UIProgressBar::Initialize()
{
    // フレーム画像の読込
    frameImage_.filePath_ = "Images/Bar_Frame.png";
    frameImage_.handle_ = Image::Load(frameImage_.filePath_);

    // ゲージ画像の読込
    gaugeImage_.filePath_ = "Images/Bar_Gauge.png";
    gaugeImage_.handle_ = Image::Load(gaugeImage_.filePath_);
}

void UIProgressBar::Update()
{
    // 参照するゲージコンポーネントがいない場合は、処理を終了
    if (referenceGauge_.this_ == nullptr) return;

    // ゲージの最大値と現在値を取得
    max_ = referenceGauge_.this_->GetMax();
    now_ = referenceGauge_.this_->GetNow();

    // ゲージのスケールを計算
    gaugeImage_.transform_ = transform_;
    gaugeImage_.transform_.scale_.x = (now_ / max_) * frameImage_.transform_.scale_.x;  

    // フレームのスケールを設定
    frameImage_.transform_ = transform_;
}

void UIProgressBar::Draw()
{
    // フレーム画像とゲージ画像が読み込まれていない場合は、処理を終了
    if (frameImage_.handle_ < 0)return;
    if (gaugeImage_.handle_ < 0)return;

    // ゲージの画像を描画
    Image::SetTransform(gaugeImage_.handle_,gaugeImage_.transform_);
    Image::Draw(gaugeImage_.handle_, Direct3D::SHADER_BAR, gaugeImage_.color_);

    // フレームの画像を描画
    Image::SetTransform(frameImage_.handle_, frameImage_.transform_);
    Image::Draw(frameImage_.handle_);
}

void UIProgressBar::Release()
{

}

void UIProgressBar::Save(json& saveObj)
{
    // ゲージ画像の情報を保存
    saveObj["gaugeImage_"]["filePath_"] = gaugeImage_.filePath_;
    saveObj["gaugeImage_"]["color_"] = { REFERENCE_XMFLOAT3(gaugeImage_.color_)};
    
    // フレーム画像の情報を保存
    saveObj["frameImage_"]["filePath_"] = frameImage_.filePath_;

    // 参照するゲージコンポーネントの情報を保存
    saveObj["referenceGauge_"]["thisName_"] = referenceGauge_.this_->GetName();
}

void UIProgressBar::Load(json& loadObj)
{
    // ゲージ画像の情報を読込
    if (loadObj.contains("gaugeImage_")) {
		
        // ゲージ画像のファイルパスを取得
        gaugeImage_.filePath_ = loadObj["gaugeImage_"]["filePath_"].get<string>();

        // ゲージ画像を読み込む
        gaugeImage_.handle_ = Image::Load(gaugeImage_.filePath_);

        // ゲージの色を取得
		gaugeImage_.color_ = { loadObj["gaugeImage_"]["color_"][0].get<float>(),loadObj["gaugeImage_"]["color_"][1].get<float>(), loadObj["gaugeImage_"]["color_"][2].get<float>() };
	}   

    // フレーム画像の情報を読込
    if (loadObj.contains("frameImage_")) {

		// フレーム画像のファイルパスを取得
		frameImage_.filePath_ = loadObj["frameImage_"]["filePath_"].get<string>();

		// フレーム画像を読み込む
		frameImage_.handle_ = Image::Load(frameImage_.filePath_);
	}

    // 参照するゲージコンポーネントの情報を読込
    if (loadObj.contains("referenceGauge_")) {

		// ゲージコンポーネントの名前を取得
		referenceGauge_.thisName_ = loadObj["referenceGauge_"]["thisName_"].get<string>();
	}
}

void UIProgressBar::DrawData()
{
    // ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
    // プログレスバーのフレーム画像を設定
    // ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
    if (ImGui::TreeNode("frame_")) {

        // 現在のファイルパスを表示
        ImGui::Text("imageFilePath_:%s", frameImage_.filePath_.c_str());
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
                frameImage_.filePath_ = ofn.lpstrFile;
                frameImage_.filePath_ = FileManager::GetAssetsRelativePath(frameImage_.filePath_);
                FileManager::ReplaceBackslashes(frameImage_.filePath_);
                SetCurrentDirectory(defaultCurrentDir);

                // フレーム画像を読み込む
                frameImage_.handle_ = Image::Load(frameImage_.filePath_);
            }
            else {
                ImGui::TreePop();
                return;
            }
        }
        ImGui::TreePop();
    }

    if (ImGui::TreeNode("gauge_")) {

        // ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
        // ゲージ表示色を設定
        // ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
        ImVec4 inputCol = { REFERENCE_XMFLOAT3(gaugeImage_.color_),0 };
        ImGui::ColorEdit4("Color", (float*)&inputCol);
        gaugeImage_.color_ = { REFERENCE_XMFLOAT3(inputCol) };

        // ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
        // 参照ゲージコンポーネントを選択
        // ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
        vector<gauge> gauges;
        vector<StageObject*> objects = ((Stage*)FindObject("Stage"))->GetStageObjects();

        //ステージ内のオブジェクトを参照してすべてのゲージコンポーネントを取得
        for (auto obj : objects) {
            //HPゲージを探して取得
            auto healthGaugeComp = obj->FindComponent(HealthGauge);
            if (healthGaugeComp.empty() == false)
                for (auto healthGaugeComp : healthGaugeComp) {
                    //配列にオブジェクトとコンポーネントを一つにまとめて入れる？
                    auto gaugeComp = dynamic_cast<Component_Gauge*>(healthGaugeComp);
                    if (gaugeComp == nullptr)continue;
                    gauges.push_back({ obj,gaugeComp,obj->GetObjectName(),gaugeComp->GetName() });
                }
            //技ゲージ...
        }
        static int select = 0;

        // select の範囲をチェック
        if (select >= gauges.size()) {
            select = 0;
        }

        //コンボボックスでgaugeのコンテナにあるselect番目のコンポーネントを文字列に変換して受け取る？
        if (gauges.empty() == false)
            if (ImGui::BeginCombo("gauge_", referenceGauge_.thisName_.c_str())) {
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

                // select の範囲をチェックしてから設定
                if (select < gauges.size()) {
                    referenceGauge_ = gauges[select];
                }
            }

        ImGui::TreePop();
    }

    // ゲージの制御
    ImGui::DragFloat("Current Value", &now_, 1.f, max_);
    ImGui::DragFloat("Max Value", &max_, 1.f);
    ImGui::ProgressBar(now_ / max_, ImVec2(0.0f, 0.0f));

}


void UIProgressBar::SetGaugeMaxValue(float _maxValue)
{
    max_ = _maxValue;
}

void UIProgressBar::SetGaugeCurrentValue(float _nowValue) {
    now_ = _nowValue;
}
