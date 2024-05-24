#include "Scene_Test.h"

// インクルード
#include "../../Engine/ImGui/imgui.h"
#include "../Objects/Stage/SkySphere.h"
#include "../../TestObject_Box.h"

Scene_Test::Scene_Test(GameObject * parent)
	: GameObject(parent, "Scene_Test"),pStage_(nullptr)
{
}

void Scene_Test::Initialize()
{
	// スカイスフィアを標準で生成
	//Instantiate<SkySphere>(this);

	// テストオブジェクトを生成
	Instantiate<TestObject_Box>(this);


}

void Scene_Test::Update()
{
}

void Scene_Test::Draw()
{
}

void Scene_Test::Release()
{
}
