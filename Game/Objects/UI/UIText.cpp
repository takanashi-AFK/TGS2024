#include "UIText.h"
#include "../../../Engine/ResourceManager/Text.h"
#include "../../../Engine/ImGui/imgui.h"
#include "../../../Engine/DirectX/Direct3D.h"
#include "../../../Engine/Global.h"

UIText::UIText(string _name, UIObject* parent,int _layerNum)
	: UIObject(_name, UI_TEXT, parent, _layerNum), pText_(nullptr), drawText_(""), size_(1.f), intNum_(nullptr)
{
}

void UIText::Initialize()
{
	// テキストオブジェクトを生成＆初期化
	pText_ = new Text;
	pText_->Initialize();

	LockScale();
	LockRotate();

}

void UIText::Update()
{
	OpenChangeFontDialog();
}

void UIText::Draw()
{
	// 表示サイズを計算
	pText_->SetScale(size_);

	// 表示位置を計算
	float drawX = (transform_.position_.x * (Direct3D::screenWidth_ / 2)) + (Direct3D::screenWidth_ / 2);		
	float drawY = (transform_.position_.y * (Direct3D::screenHeight_ / 2)) + (Direct3D::screenHeight_ / 2);
	
	// テキストを描画
	if (intNum_ == nullptr)pText_->Draw(drawX, drawY, drawText_.c_str());
	else pText_->Draw(drawX, drawY,*intNum_);
}

void UIText::Release()
{
	// テキストオブジェクトの解放
	pText_->Release();
}

void UIText::Save(json& saveObj)
{
	saveObj["text"] = drawText_;
	saveObj["size"] = size_;
	saveObj["fontFilePath"] = fontFilePath_;
	saveObj["charWidth"] = charWidth;
	saveObj["charHeight"] = charHeight;
	saveObj["rowLength"] = rowLength;
}

void UIText::Load(json& loadObj)
{
	if (loadObj.contains("text"))drawText_ = loadObj["text"].get<string>();
	if (loadObj.contains("size"))size_ = loadObj["size"].get<float>();
	if (loadObj.contains("fontFilePath"))fontFilePath_ = loadObj["fontFilePath"].get<string>();
	if (loadObj.contains("charWidth"))charWidth = loadObj["charWidth"].get<int>();
	if (loadObj.contains("charHeight"))charHeight = loadObj["charHeight"].get<int>();
	if (loadObj.contains("rowLength"))rowLength = loadObj["rowLength"].get<int>();

	if (fontFilePath_ != "") {
		pText_ = new Text;
		pText_->Initialize(fontFilePath_.c_str(), charWidth, charHeight, rowLength);
	}
}

void UIText::DrawData()
{
	// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	// 表示するテキストを変更
	// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	if(intNum_ == nullptr)
	if (ImGui::TreeNode("TextString")) {
		ImGui::Text("Current Text : %s", drawText_.c_str());
		char buffer[256] = "";
		if (ImGui::InputTextWithHint("##Input", "Input New Text...", buffer, IM_ARRAYSIZE(buffer)))
			this->drawText_ = buffer;
		ImGui::TreePop();
	}

	// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	// フォントサイズを変更
	// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	ImGui::DragFloat("size", &size_, 0.01f);


	if (ImGui::Button("ChangeFont")) {
		openChangeFontDialog_ = true;
	}
}

void UIText::OpenChangeFontDialog()
{
	if(openChangeFontDialog_){
		ImGui::Begin("ChangeFont");
	

		if (ImGui::Button("Select fontPath")) {
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
					ofn.lpstrFilter = TEXT("PNGファイル(*.png)\0*.png\0すべてのファイル(*.*)\0*.*\0"); // フィルター（FBXファイルのみ表示）
					ofn.nFilterIndex = 1; // 初期選択するフィルター
					ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST; // フラグ（ファイルが存在すること、パスが存在することを確認）
					ofn.lpstrInitialDir = TEXT("."); // カレントディレクトリを初期選択位置として設定
				}

				// ファイルを選択するダイアログの表示
				if (GetOpenFileName(&ofn) == TRUE) {
					// ファイルパスを取得
					fontFilePath_ = ofn.lpstrFile;

					// カレントディレクトリからの相対パスを取得
					fontFilePath_ = FileManager::GetAssetsRelativePath(fontFilePath_);

					// 文字列内の"\\"を"/"に置換
					FileManager::ReplaceBackslashes(fontFilePath_);

					// ディレクトリを戻す
					SetCurrentDirectory(defaultCurrentDir);


				}
				else {
					return;
				}
			}
		}
			ImGui::Text("%s", fontFilePath_.c_str());
			ImGui::DragInt("charWidth", &charWidth);
			ImGui::DragInt("charHeight", &charHeight);
			ImGui::DragInt("rowLength", &rowLength);

			if (ImGui::Button("confirm")) {

				if (fontFilePath_ == "") {
					ImGui::TextColored(ImVec4(1, 0, 0, 1), "Please Select FilePath");
				}
				else {
					pText_ = new Text;
					pText_->Initialize(fontFilePath_.c_str(), charWidth, charHeight, rowLength);
				}
			}


		ImGui::End();
	}

}
