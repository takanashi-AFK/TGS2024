#include "GameEditor.h"
#include "../../Engine/ImGui/imgui.h"
#include "../../Engine/DirectX/Direct3D.h"
#include "../Objects/Stage/Stage.h"
#include "../Objects/Stage/StageObject.h"
#include "../Objects/UI/UIPanel.h"
#include "../Objects/UI/UIObject.h"
#include "../../Engine/Global.h"
#include "../../Engine/DirectX/Texture.h"
#include "../../Engine/GameObject/Camera.h"
#include "../Objects/Camera/TPSCamera.h"

using namespace FileManager;

namespace {
	Texture* pTexture_camera = nullptr;
}


GameEditor::GameEditor(GameObject* _parent)
	:GameObject(_parent, "StageEditor"), editStage_(nullptr), selectEditStageObjectIndex_(-1), editUIPanel_(nullptr), selectEditUIObjectIndex_(-1), editType_(NONE),cameraType_(TPS)
{
}

void GameEditor::Initialize()
{
	// カメラ画像のテクスチャを読み込む
	pTexture_camera = new Texture();
	pTexture_camera->Load("Images/GUI_Camera.png");

	// カメラの位置を取得
	cameraPosition_ = Camera::GetPosition();
	cameraTarget_ = Camera::GetTarget();
}

void GameEditor::Update()
{
}

void GameEditor::Draw()
{
	// ワールドアウトライナーを描画
	DrawWorldOutLiner();

	// 詳細ウィンドウを描画
	DrawDatails();

	// UIオブジェクト作成ウィンドウを描画
	if(isShowCreateUIObjectWindow_)UIObjectClreateWindow();
}

void GameEditor::Release()
{
}

void GameEditor::DrawWorldOutLiner()
{
	// ImGuiで表示するウィンドウの設定を行う
	ImGui::SetNextWindowPos(ImVec2(Direct3D::screenWidth_ * 0.7f, 0));
	ImGui::SetNextWindowSize(ImVec2(Direct3D::screenWidth_ * 0.3f, Direct3D::screenHeight_ * 0.5f));

	// 固定ウィンドウを表示
	ImGui::Begin("World Outliner", NULL,
		ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse| ImGuiWindowFlags_AlwaysHorizontalScrollbar);
	{
		ImGui::BeginTabBar("tab Ber");{

			// ステージオブジェクトのタブを表示
			if(editStage_ != nullptr)
				if (ImGui::BeginTabItem("StageObject")) {
					DrawStageOutLiner();
					editType_ = STAGE;
					ImGui::EndTabItem();
				}

			// UIオブジェクトのタブを表示
			if(editUIPanel_ != nullptr)
				if (ImGui::BeginTabItem("UIPanel")) {
					DrawUIPanelOutLiner();
					editType_ = UIPANEL;
					ImGui::EndTabItem();
				}

			// カメラのタブを表示
			if (ImGui::BeginTabItem("Camera")) {
				ImGui::Image(pTexture_camera->GetSRV(), ImVec2(16*23, 9*23));

				ImGui::Dummy(ImVec2(0, 10));
				// ラジオボタン
				ImGui::Text("Camera type");
				if (ImGui::RadioButton("default camera", cameraType_ == DEFAULT))cameraType_ = DEFAULT;
				if (ImGui::RadioButton("tps camera", cameraType_ == TPS))cameraType_ = TPS;

				editType_ = CAMERA;
				ImGui::EndTabItem();
			}
		}
		ImGui::EndTabBar();
	}
	ImGui::End();
}

void GameEditor::DrawStageOutLiner()
{
	ImGui::Text("StageObject menu");

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
			if (ImGui::Selectable(editStage_->GetStageObjects()[i]->GetObjectName().c_str(), selectEditStageObjectIndex_ == i)) {
				selectEditStageObjectIndex_ = i;
			}
	}
	ImGui::EndChild();
}

void GameEditor::DrawUIPanelOutLiner()
{
	ImGui::Text("UIObject menu");

	if (ImGui::Button("Add"))AddUIObject();
	ImGui::SameLine();

	if (ImGui::Button("Save"))SaveUIPanel();
	ImGui::SameLine();

	if (ImGui::Button("Load"))LoadUIPanel();
	ImGui::SameLine();

	if (ImGui::Button("Delete"))editUIPanel_->DeleteAllUIObject();

	ImGui::Separator();

	ImGui::BeginChild("ObjectList"); {
		// リストを表示
		for (int i = 0; i < editUIPanel_->GetUIObjects().size(); ++i)
			if (ImGui::Selectable(editUIPanel_->GetUIObjects()[i]->GetObjectName().c_str(), selectEditUIObjectIndex_ == i)) {
				selectEditUIObjectIndex_ = i;
			}
	}
	ImGui::EndChild();
}

void GameEditor::DrawDatails()
{
	// ImGuiで表示するウィンドウの設定を行う
	ImGui::SetNextWindowPos(ImVec2(Direct3D::screenWidth_ * 0.7f, Direct3D::screenHeight_ * 0.5f));
	ImGui::SetNextWindowSize(ImVec2(Direct3D::screenWidth_ * 0.3f, Direct3D::screenHeight_ * 0.5f));

	// 固定ウィンドウを表示
	ImGui::Begin("Details", NULL,
				ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_AlwaysHorizontalScrollbar);
	{
		switch (editType_)
		{
		case STAGE:DrawStageObjectDatails(); break;
		case UIPANEL:DrawUIObjectDatails();break;
		case CAMERA:DrawDatalsCamera(); break;
		default:ImGui::Text("No information to display");break;
		}
	}
	ImGui::End();
}

void GameEditor::DrawStageObjectDatails()
{
	if (editStage_ == nullptr)return;

	if (selectEditStageObjectIndex_ >= 0 && selectEditStageObjectIndex_ < editStage_->GetStageObjects().size()) {

		editStage_->GetStageObjects()[selectEditStageObjectIndex_]->DrawData();
	}
	else ImGui::Text("No object selected");
}

void GameEditor::DrawUIObjectDatails()
{
	if (editUIPanel_ == nullptr)return;

	if (selectEditUIObjectIndex_ >= 0 && selectEditUIObjectIndex_ < editUIPanel_->GetUIObjects().size()) {

		editUIPanel_->GetUIObjects()[selectEditUIObjectIndex_]->ChildDrawData();
	}
	else ImGui::Text("No object selected");
}

void GameEditor::DrawDatalsCamera()
{
	ImGui::Text("Camera menu");
	switch (cameraType_)
	{
	case DEFAULT:
		tpsCamera_->SetActive(false);
		// カメラの位置を設定
		ImGui::DragFloat3("Camera position", &cameraPosition_.x);
		// カメラの焦点を設定
		ImGui::DragFloat3("Camera target", &cameraTarget_.x);
		// カメラの位置を設定
		Camera::SetPosition(cameraPosition_);
		// カメラの焦点を設定
		Camera::SetTarget(cameraTarget_);
		break;

	case TPS:
		// 保存ボタン
		if (ImGui::Button("save")) {
			json saveObj;
			tpsCamera_->Save(saveObj);
			JsonReader::Save("Datas/CameraLayouts/TPSCamera.json", saveObj);
		}
		ImGui::SameLine();

		// 読み込みボタン
		if (ImGui::Button("load")) {
			json loadObj;
			JsonReader::Load("Datas/CameraLayouts/TPSCamera.json", loadObj);
			tpsCamera_->Load(loadObj);
		}

		ImGui::Separator();

		// 設定用のウィンドウを表示
		tpsCamera_->DrawData();

		break;
	}
}

void GameEditor::UIObjectClreateWindow()
{
	static char nameBuffer[256] = "";
	if (isShowCreateUIObjectWindow_) {
		ImGui::Begin("Create UIObject", &isShowCreateUIObjectWindow_); {

			ImGui::NewLine();
			ImGui::Text("Set the details of the object to be generated!!");
			ImGui::Separator();

			// 名前を入力
			ImGui::InputTextWithHint(":seting name", "Input object name...", nameBuffer, IM_ARRAYSIZE(nameBuffer));

			// タイプを選択
			static UIType uitype = UIType::UI_NONE;	// 初期選択項目
			static std::string type = "NONE";		// 初期選択項目

			if (ImGui::BeginCombo(":seting type", type.c_str())) {
				for (int i = 0; i < UIType::UI_MAX; i++) {
					bool isSelected = (type == GetUITypeString((UIType)i));
					if (ImGui::Selectable(GetUITypeString((UIType)i).c_str(), isSelected)) {
						type = GetUITypeString((UIType)i);
						uitype = (UIType)i;
					}
					if (isSelected) {
						ImGui::SetItemDefaultFocus();
					}
				}
				ImGui::EndCombo();
			}

			// 生成ボタン
			if (ImGui::Button("Create")) {
				// UIオブジェクトを作成・追加
				UIObject* obj = CreateUIObject(nameBuffer, uitype, editUIPanel_);
				if (obj != nullptr) {
					editUIPanel_->AddUIObject(obj);
					isShowCreateUIObjectWindow_ = false;
				}
			}
		}
		ImGui::End();
	}
}

void GameEditor::AddStageObject()
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

void GameEditor::SaveStage()
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

void GameEditor::LoadStage()
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

void GameEditor::AddUIObject()
{
	isShowCreateUIObjectWindow_ = true;
}

void GameEditor::SaveUIPanel()
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
	editUIPanel_->Save(saveObj);
	if (JsonReader::Save(filePath, saveObj) == false) MessageBox(NULL, "保存に失敗しました。", 0, 0);
}

void GameEditor::LoadUIPanel()
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
	editUIPanel_->Load(loadObj);
}
