#include "Scene_Play.h"

#include"../Objects/Stage/SkySphere.h"
#include"../Objects/Stage/Stage.h"
#include"../Otheres/GameEditor.h"
#include"../../Engine/ImGui/imgui.h"
#include"../Objects/Stage/Components/HealthManagerComponents/Component_HealthManager.h"
#include"../Objects/Stage/Components/BehaviorComponents/Component_PlayerBehavior.h"
#include"../../Engine/SceneManager.h"
Scene_Play::Scene_Play(GameObject* parent)
{
}

void Scene_Play::Initialize()
{
	Instantiate<SkySphere>(this);

	Stage* pStage = Instantiate<Stage>(this);

	// ステージを読み込み
	json stageData;
	JsonReader::Load("Datas/stage_Test00_sugawara.json", stageData);
	pStage->Load(stageData);
	
	//範囲for分でオブジェクトリストの取得
	for (auto pList : pStage->GetStageObjects()){
		//リスト内でとうろくされているPlayerBehaviorがあったらコンポーネントをキャストして代入
		if (pList->FindComponent("PlayerBehavior")) {
			Component_PlayerBehavior* playerBeha = dynamic_cast<Component_PlayerBehavior*>(pList->FindComponent("PlayerBehavior"));
			if (playerBeha != nullptr) {
				//playerBehaから子コンポーネントを取得する
				health_ =dynamic_cast<Component_HealthManager*>(playerBeha->GetChildComponent("HealthManager"));
			}
		}
	}

#ifdef _DEBUG

	// ステージエディターを実行
	GameEditor* pSe = Instantiate<GameEditor>(this);
	
	// 編集対象を設定
	pSe->SetEditStage(pStage);

#endif // _DEBUG

}

void Scene_Play::Update()
{
	//HPが0になったらエンドシーンに移行
	if (health_->GetHP() == 0) {
		SceneManager* pChangeScene = (SceneManager*)FindObject("SceneManager");
		pChangeScene->ChangeScene(SCENE_ID_END, TID_BLACKOUT);
	}
	
	
}

void Scene_Play::Draw()
{
}

void Scene_Play::Release()
{
}
