#pragma once

// インクルード
#include <string>

// using宣言
using std::string;

// ファイルパスの定数を定義
namespace Constants {

	/// スプラッシュシーン ///
	const string SPLASH_SCENE_LAYOUT_JSON = "Datas/UILayouts/splashScene_layout.json";

	/// タイトルシーン ///
	const string TITLE_SCENE_LAYOUT_JSON = "Datas/UILayouts/titleScene_layout.json";
	const string TITLE_SCENE_START_BUTTON_NAME = "title_startButton";
	const string TITLE_SCENE_RANKING_BUTTON_NAME = "rankingScene_changeButton";

	/// プレイシーン ///
	const string PLAY_SCENE_LAYOUT_JSON = "test_playerHPBar.json";
	const string PLAY_SCENE_STAGE_LAYOUT_JSON = "Stage02.json";
	const string PLAY_SCENE_CAMERA_LAYOUT_JSON = "Datas/CameraLayouts/TPSCamera.json";
	const string PLAY_SCENE_TIMER_NAME = "Timer";

	/// リザルトシーン ///
	const string RESULT_SCENE_LAYOUT_JSON = "Datas/UILayouts/ResultScene_layout.json";
	const string RESULT_SCENE_STAGE_LAYOUT_JSON = "Datas/StageLayouts/EndSceneStage.json";
	const string RESULT_SCENE_HP_TEXT_NAME = "HPNum";
	const string RESULT_SCENE_TIME_TEXT_NAME = "TimeNum";
	const string RESULT_SCENE_SCORE_TEXT_NAME = "ScoreNum";
	const string RESULT_SCENE_NEXT_BUTTON_NAME = "NextSceneButton";

	/// エンドシーン ///
	const string END_SCENE_LAYOUT_JSON = "Datas/UILayouts/endScene_layout.json";

	/// ランキングシーン ///
	const string RANKING_SCENE_LAYOUT_JSON = "Datas/UILayouts/rankingScene_layout.json";
	const string RANKING_SCENE_RETURN_BUTTON_NAME = "returnButton";

	/// テストシーン ///
	const string TEST_SCENE_CAMERA_LAYOUT_JSON = "Datas/CameraLayouts/camera.json";

	// データ
	const string RANKING_DATA_CSV = "ranking.csv";

}