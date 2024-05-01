#include "TestScene.h"
#include "../Objects/Stage/Stage.h"
#include "../../Engine/ImGui/imgui.h"


//コンストラクタ
TestScene::TestScene(GameObject * parent)
	: GameObject(parent, "TestScene")
{
}

//初期化
void TestScene::Initialize()
{
	pStage_ = Instantiate<Stage>(this);
}

//更新
void TestScene::Update()
{
	if (ImGui::Button("Save")) {
		json saveObj;
		pStage_->Save(saveObj);
		JsonReader::Save("testData.json", saveObj);
	}

	ImGui::SameLine();

	if (ImGui::Button("Load")) {
		json loadObj;
		JsonReader::Load("testData.json", loadObj);
		pStage_->Load(loadObj);
	}
}

//描画
void TestScene::Draw()
{
}

//開放
void TestScene::Release()
{
}
