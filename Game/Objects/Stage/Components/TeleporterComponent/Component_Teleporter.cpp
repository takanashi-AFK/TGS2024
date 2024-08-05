#include "Component_Teleporter.h"
#include "../DetectorComponents/Component_CircleRangeDetector.h"
#include "../../StageObject.h"
#include "../../../../../Engine/GameObject/GameObject.h"
#include "../../../../../Engine/ImGui/imgui.h"
#include "../TimerComponent/Component_Timer.h"
#include "../../../../../Engine/Global.h"
#include "../MoveComponents/Component_WASDInputMove.h"
#include "../../../../../Engine/Global.h"
Component_Teleporter::Component_Teleporter(string _name, StageObject* _holder, Component* _parent)
:Component(_holder, _name, Teleporter, _parent)
{
}

void Component_Teleporter::Initialize()
{
	// 子コンポーネントの追加
	if (FindChildComponent("CircleRangeDetector") == false)AddChildComponent(CreateComponent("CircleRangeDetector", CircleRangeDetector, holder_, this));
	if (FindChildComponent("Timer") == false)AddChildComponent(CreateComponent("Timer", Timer, holder_, this));
}

void Component_Teleporter::Update()
{
	if (!isActive_)return;

	auto detector = dynamic_cast<Component_CircleRangeDetector*>(GetChildComponent("CircleRangeDetector"));
	if (detector == nullptr)return;
	auto timer = dynamic_cast<Component_Timer*>(GetChildComponent("Timer"));
	if (timer == nullptr)return;
	//// PlayerBehaviorを持つオブジェクトを検索
	//auto playerList = ((Stage*)holder_->GetParent())->GetStageObjects();
	//for (auto a : playerList) {

	//	StageObject* pl = a;
	//	if (pl != nullptr) {

	//		if (pl->FindComponent("PlayerBehavior")) {
	//			playerBehavior_ = pl->FindComponent("PlayerBehavior");
	//			target_ = pl;
	//			break;
	//		}
	//	}
	//}

	// 検出対象の設定
	detector->SetTarget(target_);

	if (detector->IsContains()) {
		Teleport();
	}

	if (isTeleport_ == true) {
		// タイマー開始
		timer->SetTime(0.5f);
		timer->Start();

		// タイマー終了
		if (timer->GetIsEnd()) {
			// ターゲットのWASDを探す(2個以上ついていない想定)
			if (target_ != nullptr) {
				auto inputMove = target_->FindComponent(WASDInputMove);
				if (inputMove.empty())return;
				for (auto iMove : inputMove) {
					iMove->Execute();
					break;
				}
			}
			timer->Reset();
			isTeleport_ = false;
		}
	}
}

void Component_Teleporter::Release()
{
}

void Component_Teleporter::Save(json& _saveObj)
{
}

void Component_Teleporter::Load(json& _loadObj)
{
}

void Component_Teleporter::DrawData()
{
	ImGui::Checkbox("isActive", &isActive_);
	ImGui::Combo("ChangeType", (int*)&changeType_, "CHANGE_TELEPORT\0CHANGE_SCENE\0CHANGE_JSON\0");
	if (changeType_ == CHANGE_TELEPORT) {
		ImGui::DragFloat3("TeleportPos", &teleportPos_.x, 0.1f);
	}
	else if (changeType_ == CHANGE_SCENE) {
		ImGui::InputInt("ChangeSceneID", (int*)&changeSceneID_);
	}
	else if (changeType_ == CHANGE_JSON) {
		if (ImGui::Button("...")) {

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
					ofn.lpstrFilter = TEXT("jsonファイル(*.json)\0*.json\0すべてのファイル(*.*)\0*.*\0"); // フィルター（FBXファイルのみ表示）
					ofn.nFilterIndex = 1; // 初期選択するフィルター
					ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST; // フラグ（ファイルが存在すること、パスが存在することを確認）
					ofn.lpstrInitialDir = TEXT("."); // カレントディレクトリを初期選択位置として設定
				}

				// ファイルを選択するダイアログの表示
				if (GetOpenFileName(&ofn) == TRUE) {
					// ファイルパスを取得
					changeJsonPath_ = ofn.lpstrFile;

					// カレントディレクトリからの相対パスを取得
					changeJsonPath_ = FileManager::GetAssetsRelativePath(changeJsonPath_);

					// 文字列内の"\\"を"/"に置換
					FileManager::ReplaceBackslashes(changeJsonPath_);

					// ディレクトリを戻す
					SetCurrentDirectory(defaultCurrentDir);
				}
				else {
					return;
				}
			}ImGui::SameLine();
		}
			ImGui::Text(changeJsonPath_.c_str());

	}

	//対象の選択
	vector<string> objNames;
	objNames.push_back("null");

	for (auto obj : ((Stage*)holder_->GetParent())->GetStageObjects())objNames.push_back(obj->GetObjectName());

	static int select = 0;
	if (ImGui::BeginCombo("target_", objNames[select].c_str())) {
		for (int i = 0; i < objNames.size(); i++) {
			bool is_selected = (select == i);
			if (ImGui::Selectable(objNames[i].c_str(), is_selected))select = i;
			if (is_selected)ImGui::SetItemDefaultFocus();
		}
		ImGui::EndCombo();
	}

	if (select == 0)target_ = nullptr;
	else target_ = (StageObject*)holder_->FindObject(objNames[select]);
}

void Component_Teleporter::Teleport()
{
	auto timer = dynamic_cast<Component_Timer*>(GetChildComponent("Timer"));
	if (timer == nullptr)return;
	static bool isEffectEnd = false;
	static bool isEffectNow = false;

	if (isEffectEnd == false) {

		// タイマー開始
		timer->SetTime(3.f);
		timer->Start();

		// ターゲットのWASDを探す
		if (target_ != nullptr) {
			auto inputMove = target_->FindComponent(WASDInputMove);
			if (inputMove.empty())return;
			for (auto iMove : inputMove) {
				iMove->Stop();
				break;
			}
		}

		if (timer->GetIsEnd()) {
			isEffectNow = true;
			timer->Reset();
		}
	}
	
	// タイマー終了
	if (isEffectNow == true) {

		// 演出
		if (changeType_ == CHANGE_TELEPORT) {
			// teleportPos_への座標変更
			target_->SetPosition(teleportPos_);
		}
		//else if (changeType_ == CHANGE_SCENE) {
		//	// ChangeSceneName_へのシーン遷移
		//	SceneManager* sceneManager = (SceneManager*)holder_->GetParent()->FindObject("SceneManager");
		//	sceneManager->ChangeScene(changeSceneID_, TID_BLACKOUT);
		//}
		else if (changeType_ == CHANGE_JSON) {
			// JSONファイルの読込

			json loadData;
			if (JsonReader::Load(changeJsonPath_, loadData)) {
				// ステージを作成
				json loadObj;
				if (JsonReader::Load(changeJsonPath_, loadObj) == false) MessageBox(NULL, "読込に失敗しました。", 0, 0);
				((Stage*)holder_->GetParent())->Load(loadObj);
			}
		}
		isEffectNow = false;
		isTeleport_ = true;
	}


}

void Component_Teleporter::Execute(ChangeType _ch)
{
	isActive_ = true;
	changeType_ = _ch;
}
