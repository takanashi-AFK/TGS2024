#include "Scene_Ranking.h"

// インクルード
#include "../Objects/UI/UIPanel.h"
#include "../Otheres/RankingManager.h"
#include "../Objects/UI/UIButton.h"
#include "../../Engine/SceneManager.h"
#include "../Objects/UI/UIText.h"
#include "../Constants.h"

using namespace Constants;

Scene_Ranking::Scene_Ranking(GameObject* _parent)
	: GameObject(_parent, "Scene_Ranking")
{
}

void Scene_Ranking::Initialize()
{
	// UIパネルを取得
	UIPanel* panel = UIPanel::GetInstance();
	
	// UILayout_jsonファイルを読み込む
	json loadData;
	if (JsonReader::Load(RANKING_SCENE_LAYOUT_JSON, loadData)) panel->Load(loadData);
	
	// ランキングデータを読み込む
	RankingManager::GetInstance().Load(RANKING_DATA_CSV);

	// ランキングデータを表示
	{
		// ランキングデータを取得 ※5位まで
		for (int i = 1; i <= 5; i++) {

			// ユーザーネームを取得
			{
				// UIテキスト名を取得
				std::string name = "rank" + std::to_string(i) + "_userName";
				UIText* text = (UIText*)panel->GetUIObject(name);

				// ユーザーネームを取得
				string userName = RankingManager::GetInstance().GetUser(i - 1);

				// テキストにユーザーネームを設定
				if (text != nullptr) text->SetText(userName);
			}
			
			// スコアを取得
			{
				// UIテキスト名を取得
				std::string name = "rank" + std::to_string(i) + "_scoreNum";
				UIText* text = (UIText*)panel->GetUIObject(name);

				// スコアを取得
				string score = std::to_string(RankingManager::GetInstance().GetScore(i - 1));

				// テキストにスコアを設定
				if (text != nullptr) text->SetText(score);
			}
		}
	}

}

void Scene_Ranking::Update()
{
	UIButton* returnButton = (UIButton*)UIPanel::GetInstance()->GetUIObject(RANKING_SCENE_RETURN_BUTTON_NAME);
	// ボタンが押されたらシーンを切り替える
	if (returnButton != nullptr) if (returnButton->OnClick() == true) {

		// シーンを切り替える
		SceneManager* sceneManager = (SceneManager*)FindObject("SceneManager");
		sceneManager->ChangeScene(SCENE_ID_TITLE, TID_BLACKOUT);
	}
}

void Scene_Ranking::Draw()
{
}

void Scene_Ranking::Release()
{
}
