#include "Scene_Test.h"

// インクルード
#include "../Objects/Stage/SkySphere.h"
#include "../Objects/Stage/Stage.h"
#include "../Otheres/StageEditor.h"

//UIButton追加インクルード
#include "../Objects/UI/UIButton.h"
#include "../../Engine/DirectX/Input.h"
#include "../../Engine/ImGui/imgui.h"

//UIPanel追加インクルード
#include "../Objects/UI/UIPanel.h"

Scene_Test::Scene_Test(GameObject * parent)
	: GameObject(parent, "Scene_Test")
{
}

void Scene_Test::Initialize()
{
	// スカイスフィアを標準で生成
	Instantiate<SkySphere>(this);

	panel = Instantiate<UIPanel>(this);

	//button = Instantiate<UIButton>(this);

	/*

	// ステージを作成
	Stage* pStage = Instantiate<Stage>(this);

#ifdef _DEBUG

	// ステージエディターを実行
	StageEditor* pSe = Instantiate<StageEditor>(this); 

	// 編集対象を設定
	pSe->SetEditTarget(pStage);
	
#endif // _DEBUG

	*/
}

void Scene_Test::Update()
{
	/*
 if (button->ClickButton())
	{
		PostQuitMessage(0);
	}
 */


	panel->Update();
}

void Scene_Test::Draw()
{
	panel->Draw();
}

void Scene_Test::Release()
{
	if (panel != nullptr)
	{
		panel->Release();
	}
}
