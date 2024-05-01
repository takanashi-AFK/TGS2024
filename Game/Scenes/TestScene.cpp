#include "TestScene.h"
#include "../Objects/Stage/StageObject.h"
#include "../../Engine/ImGui/imgui.h"

#include "../Objects/Stage/Components/RotationYComponent.h"

//コンストラクタ
TestScene::TestScene(GameObject * parent)
	: GameObject(parent, "TestScene")
{
}

static StageObject* obj = nullptr;

//初期化
void TestScene::Initialize()
{
}

//更新
void TestScene::Update()
{
}

//描画
void TestScene::Draw()
{
}

//開放
void TestScene::Release()
{
}
