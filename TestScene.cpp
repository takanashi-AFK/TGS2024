#include "TestScene.h"
#include "StageObject.h"
#include "Engine/ImGui/imgui.h"

#include "RotationYComponent.h"

//コンストラクタ
TestScene::TestScene(GameObject * parent)
	: GameObject(parent, "TestScene")
{
}

static StageObject* obj = nullptr;
//初期化
void TestScene::Initialize()
{

	obj = CreateStageObject("obj", "DebugCollision/BoxCollider.fbx", this);
	obj->AddComponent(new RotationYComponent(obj));
}

//更新
void TestScene::Update()
{
	if (ImGui::Button("load")) {
		json loadObj;
		JsonReader::Load("testdata.json", loadObj);
		obj->Load(loadObj);
	}
	
	if (ImGui::Button("save")) {
		json savaObj;
		obj->Save(savaObj);
		JsonReader::Save("testdata.json", savaObj);
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
