#include "TestScene.h"

// インクルード
#include "../Objects/Stage/Stage.h"
#include "../../Engine/ImGui/imgui.h"

TestScene::TestScene(GameObject * parent)
	: GameObject(parent, "TestScene"),pStage_(nullptr)
{
}

void TestScene::Initialize()
{
	// ステージを作成
	pStage_ = Instantiate<Stage>(this);
	
	// ステージ情報を読込
	json loadObj;
	JsonReader::Load("testData.json", loadObj);
	pStage_->Load(loadObj);
}

void TestScene::Update()
{
#ifdef _DEBUG

	// 保存
	if (ImGui::Button("Save")) {
		json saveObj;
		pStage_->Save(saveObj);
		JsonReader::Save("testData.json", saveObj);
	}
	ImGui::SameLine();

	// 読込
	if (ImGui::Button("Load")) {
		json loadObj;
		JsonReader::Load("testData.json", loadObj);
		pStage_->Load(loadObj);
	}
	ImGui::SameLine();

	// 削除
	if (ImGui::Button("Delete")) {
		pStage_->DeleteAllStageObject();
	}
	ImGui::Separator();
#endif // _DEBUG
}

void TestScene::Draw()
{
}

void TestScene::Release()
{
}
