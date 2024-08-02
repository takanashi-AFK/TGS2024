#include "Component_Teleporter.h"
#include "../DetectorComponents/Component_CircleRangeDetector.h"
#include "../../StageObject.h"
#include "../../../../../Engine/GameObject/GameObject.h"
#include "../../../../../Engine/ImGui/imgui.h"
#include "../TimerComponent/Component_Timer.h"
#include "../../../../../Engine/Global.h"
#include "../MoveComponents/Component_WASDInputMove.h"

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
		//else if (changeType_ == CHANGE_JSON) {
		//	// JSONファイルの読込
		//	json loadData;
		//	if (JsonReader::Load(changeJsonPath_, loadData)) {
		//		// ステージを作成
		//		pStage_ = Instantiate<Stage>(holder_->GetParent());
		//		pStage_->Load(loadData);
		//	}
		//}
		isEffectNow = false;
		isEffectEnd = true;
	}

	if (isEffectEnd == true) {
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
					iMove->Stop();
					break;
				}
			}
				timer->Reset();
				isEffectEnd = false;
				isEffectNow = false;
		}
	}
}

void Component_Teleporter::Execute(ChangeType _ch)
{
	isActive_ = true;
	changeType_ = _ch;
}
