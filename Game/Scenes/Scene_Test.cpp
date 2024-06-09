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
	: GameObject(parent, "Scene_Test"), panel(nullptr), button(nullptr)
{

}

void Scene_Test::Initialize()
{
	// スカイスフィアを標準で生成
	Instantiate<SkySphere>(this);

	//UIPanelクラスのインスタンスを生成
	//panel = Instantiate<UIPanel>(this); //this はScene_Testのことを指してる
	//button = Instantiate<UIButton>(panel);//buttonをUIPanelの親に設定する

	////パネルのリストにbuttonを追加
	//panel->AddChild(button);


	

	// ステージを作成
	Stage* pStage = Instantiate<Stage>(this);
	
	// ステージを読み込み
	json stageData;
	JsonReader::Load("Datas/stage_Test00_sugawara.json", stageData);
	pStage->Load(stageData);


#ifdef _DEBUG

	// ステージエディターを実行
	StageEditor* pSe = Instantiate<StageEditor>(this); 

	// 編集対象を設定
	pSe->SetEditStage(pStage);
	
#endif // _DEBUG

	
}


void Scene_Test::Update()
{
	// if (button->ClickButton())PostQuitMessage(0);
}

void Scene_Test::Draw()
{
}

void Scene_Test::Release()
{

}