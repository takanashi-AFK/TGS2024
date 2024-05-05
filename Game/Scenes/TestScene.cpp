#include "TestScene.h"

// インクルード
#include "../Objects/Stage/Stage.h"
#include "../../Engine/ImGui/imgui.h"
#include "../Objects/Stage/SkySphere.h"
#include "../Otheres/StageEditor.h"

TestScene::TestScene(GameObject * parent)
	: GameObject(parent, "TestScene"),pStage_(nullptr)
{
}

void TestScene::Initialize()
{
	// スカイスフィアを標準で生成
	Instantiate<SkySphere>(this);

	// ステージを作成
	pStage_ = Instantiate<Stage>(this);

	// ステージ情報を読込
	json loadObj;
	JsonReader::Load("Datas/testData.json", loadObj);
	pStage_->Load(loadObj);

#ifdef _DEBUG
	// ステージエディターを実行
	StageEditor* pSe = Instantiate<StageEditor>(this); {

		// 編集対象を設定
		pSe->SetEditTarget(pStage_);
	}
#endif // _DEBUG
}

void TestScene::Update()
{
}

void TestScene::Draw()
{
}

void TestScene::Release()
{
}
