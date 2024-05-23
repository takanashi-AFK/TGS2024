#include "Scene_Test.h"

// インクルード
#include "../Objects/Stage/Stage.h"
#include "../../Engine/ImGui/imgui.h"
#include "../Objects/Stage/SkySphere.h"
#include "../Otheres/StageEditor.h"
#include "../../Engine/ResourceManager/Model.h"
Scene_Test::Scene_Test(GameObject * parent)
	: GameObject(parent, "Scene_Test"),pStage_(nullptr)//,handleModel1_(-1),handleModel2_(-1)
{
}

void Scene_Test::Initialize()
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

void Scene_Test::Update()
{
}

void Scene_Test::Draw()
{
	/*Model::SetTransform(handleModel1_, transform_);
	Model::Draw(handleModel1_);
	Model::SetTransform(handleModel2_, transform_);
	Model::Draw(handleModel2_);*/
}

void Scene_Test::Release()
{
}
