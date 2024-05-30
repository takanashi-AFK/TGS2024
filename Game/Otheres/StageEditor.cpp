#include "StageEditor.h"
#include "../../Engine/ImGui/imgui.h"
#include "../../Engine/DirectX/Direct3D.h"
#include "../Objects/Stage/Stage.h"
#include "../Objects/Stage/StageObject.h"

namespace {
	// 文字列内の全ての "\\" を "/" に置換する関数
	void ReplaceBackslashes(string& str) {
		size_t found = str.find("\\");
		while (found != string::npos) {
			str.replace(found, 1, "/"); // "\\" を "/" に置換する
			found = str.find("\\", found + 1); // 次の "\\" を検索する
		}
	}

	// カレントディレクトリからの相対パスを取得する関数
	std::string GetAssetsRelativePath(const std::string& absolutePath) {
		const std::string assetsFolder = "Assets\\";
		// "Assets\\" の位置を検索
		size_t assetsPos = absolutePath.find(assetsFolder);
		if (assetsPos != std::string::npos) {
			// "Assets\\" の部分を除いた、それ以降の部分を取得
			std::string relativePath = absolutePath.substr(assetsPos + assetsFolder.size());
			return relativePath;
		}
		else {
			// "Assets\\" が見つからない場合は、元のファイルパスを返す
			return absolutePath;
		}
	}

}

StageEditor::StageEditor(GameObject* _parent)
	:GameObject(_parent,"StageEditor"),editStage_(nullptr)
{
}

void StageEditor::Initialize()
{
}

void StageEditor::Update()
{
}

void StageEditor::Draw()
{
	DrawWorldOutLiner();
	DrawDatails();
}

void StageEditor::Release()
{
}

void StageEditor::DrawWorldOutLiner()
{
	// ImGuiで表示するウィンドウの設定を行う
	ImGui::SetNextWindowPos(ImVec2(Direct3D::screenWidth_ * 0.7f, 0));
	ImGui::SetNextWindowSize(ImVec2(Direct3D::screenWidth_ * 0.3f, Direct3D::screenHeight_ * 0.5f));

	// 固定ウィンドウを表示
	ImGui::Begin("World Outliner", NULL,
		ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse| ImGuiWindowFlags_AlwaysHorizontalScrollbar);
	{
		ImGui::Text("object menu");

		if (ImGui::Button("Add"))AddStageObject();
		ImGui::SameLine();

		if (ImGui::Button("Save"))SaveStage();
		ImGui::SameLine();

		if (ImGui::Button("Load"))LoadStage();
		ImGui::SameLine();

		if (ImGui::Button("Delete"))editStage_->DeleteAllStageObject();

		ImGui::Separator();

		ImGui::BeginChild("ObjectList"); {
			// リストを表示
			for (int i = 0; i < editStage_->GetStageObjects().size(); ++i)
				if (ImGui::Selectable(editStage_->GetStageObjects()[i]->GetObjectName().c_str(), selectEditObjectIndex_ == i)) {
					selectEditObjectIndex_ = i;
				}
		}
		ImGui::EndChild();
	}
	ImGui::End();
}

void StageEditor::DrawDatails()
{
	// ImGuiで表示するウィンドウの設定を行う
	ImGui::SetNextWindowPos(ImVec2(Direct3D::screenWidth_ * 0.7f, Direct3D::screenHeight_ * 0.5f));
	ImGui::SetNextWindowSize(ImVec2(Direct3D::screenWidth_ * 0.3f, Direct3D::screenHeight_ * 0.5f));

	// 固定ウィンドウを表示
	ImGui::Begin("Details", NULL,
				ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_AlwaysHorizontalScrollbar);
	{
		if (selectEditObjectIndex_ >= 0 && selectEditObjectIndex_ < editStage_->GetStageObjects().size()) {

			editStage_->GetStageObjects()[selectEditObjectIndex_]->DrawData();
		}
		else ImGui::Text("No information to display");
	}
	ImGui::End();
}

void StageEditor::AddStageObject()
{
	// 追加するオブジェクトの初期名を設定
	string name = "object" + std::to_string(editStage_->objects_.size());

	//現在のカレントディレクトリを覚えておく
	char defaultCurrentDir[MAX_PATH];
	GetCurrentDirectory(MAX_PATH, defaultCurrentDir);

	// 追加するオブジェクトのモデルファイルパスを設定
	string filePath{}; {
		// 「ファイルを開く」ダイアログの設定用構造体を設定
		OPENFILENAME ofn; {
			TCHAR szFile[MAX_PATH] = {}; // ファイル名を格納するバッファ
			ZeroMemory(&ofn, sizeof(ofn)); // 構造体の初期化
			ofn.lStructSize = sizeof(ofn); // 構造体のサイズ
			ofn.lpstrFile = szFile; // ファイル名を格納するバッファ
			ofn.lpstrFile[0] = '\0'; // 初期化
			ofn.nMaxFile = sizeof(szFile); // ファイル名バッファのサイズ
			ofn.lpstrFilter = TEXT("FBXファイル(*.fbx)\0*.fbx\0すべてのファイル(*.*)\0*.*\0"); // フィルター（FBXファイルのみ表示）
			ofn.nFilterIndex = 1; // 初期選択するフィルター
			ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST; // フラグ（ファイルが存在すること、パスが存在することを確認）
			ofn.lpstrInitialDir = TEXT("."); // カレントディレクトリを初期選択位置として設定
		}

		// ファイルを選択するダイアログの表示
		if (GetOpenFileName(&ofn) == TRUE) {
			// ファイルパスを取得
			filePath = ofn.lpstrFile;

			// カレントディレクトリからの相対パスを取得
			filePath = GetAssetsRelativePath(filePath);

			// 文字列内の"\\"を"/"に置換
			ReplaceBackslashes(filePath);

			// ディレクトリを戻す
			SetCurrentDirectory(defaultCurrentDir);
		}
		else {
			return;
		}
	}

	// オブジェクトを作成・追加
	editStage_->AddStageObject(CreateStageObject(name, filePath, editStage_));
}

void StageEditor::SaveStage()
{
	//現在のカレントディレクトリを覚えておく
	char defaultCurrentDir[MAX_PATH];
	GetCurrentDirectory(MAX_PATH, defaultCurrentDir);

	// 保存先のファイルパスを取得
	string filePath{}; {
		// 「ファイルを保存」ダイアログの設定用構造体を設定
		OPENFILENAME ofn; {
			ZeroMemory(&ofn, sizeof(ofn));
			ofn.lStructSize = sizeof(OPENFILENAME);
			ofn.lpstrFilter = TEXT("objectData(*.json)\0*.json\0すべてのファイル(*.*)\0*.*\0\0");
			char fileName[MAX_PATH] = "無題.json";
			ofn.lpstrFile = fileName;
			ofn.nMaxFile = MAX_PATH;
			ofn.Flags = OFN_OVERWRITEPROMPT;
			ofn.lpstrDefExt = "json";
			ofn.nFilterIndex = 1; // 初期選択するフィルター
			ofn.lpstrInitialDir = TEXT("."); // カレントディレクトリを初期選択位置として設定
		}

		// ファイルを保存するダイアログの表示
		if (GetSaveFileName(&ofn) == TRUE) {
			// ファイルパスを取得
			filePath = ofn.lpstrFile;

			// カレントディレクトリからの相対パスを取得
			filePath = GetAssetsRelativePath(filePath);

			// 文字列内の"\\"を"/"に置換
			ReplaceBackslashes(filePath);

			// ディレクトリを戻す
			SetCurrentDirectory(defaultCurrentDir);
		}
		else {
			return;
		}
	}

	// ファイルにステージ情報を保存
	json saveObj;
	editStage_->Save(saveObj);
	if (JsonReader::Save(filePath, saveObj) == false) MessageBox(NULL, "保存に失敗しました。", 0, 0);
	
}

void StageEditor::LoadStage()
{
	//現在のカレントディレクトリを覚えておく
	char defaultCurrentDir[MAX_PATH];
	GetCurrentDirectory(MAX_PATH, defaultCurrentDir);

	// 読み込むファイルのパスを取得
	string filePath{}; {
		// 「ファイルを開く」ダイアログの設定用構造体を設定
		OPENFILENAME ofn; {
			TCHAR szFile[MAX_PATH] = {}; // ファイル名を格納するバッファ
			ZeroMemory(&ofn, sizeof(ofn)); // 構造体の初期化
			ofn.lStructSize = sizeof(ofn); // 構造体のサイズ
			ofn.lpstrFile = szFile; // ファイル名を格納するバッファ
			ofn.lpstrFile[0] = '\0'; // 初期化
			ofn.nMaxFile = sizeof(szFile); // ファイル名バッファのサイズ
			ofn.lpstrFilter = TEXT("JSONファイル(*.json)\0*.json\0すべてのファイル(*.*)\0*.*\0"); // フィルター（FBXファイルのみ表示）
			ofn.nFilterIndex = 1; // 初期選択するフィルター
			ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST; // フラグ（ファイルが存在すること、パスが存在することを確認）
			ofn.lpstrInitialDir = TEXT("."); // カレントディレクトリを初期選択位置として設定
		}

		// ファイルを選択するダイアログの表示
		if (GetOpenFileName(&ofn) == TRUE) {
			// ファイルパスを取得
			filePath = ofn.lpstrFile;

			// カレントディレクトリからの相対パスを取得
			filePath = GetAssetsRelativePath(filePath);

			// 文字列内の"\\"を"/"に置換
			ReplaceBackslashes(filePath);

			// ディレクトリを戻す
			SetCurrentDirectory(defaultCurrentDir);
		}
		else {
			return;
		}
	}

	// ファイルを読み込みステージを生成
	json loadObj;
	if (JsonReader::Load(filePath, loadObj) == false) MessageBox(NULL, "読込に失敗しました。", 0, 0);
	editStage_->Load(loadObj);
}
