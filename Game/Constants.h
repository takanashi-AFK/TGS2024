#pragma once

// インクルード
#include <string>

// using宣言
using std::string;

// ファイルパスの定数を定義
namespace Constants{

	/// スプラッシュシーン ///
	const string SPLASH_SCENE_LAYOUT_JSON = "release/layouts/ui/splashScene_layout.json";

	/// タイトルシーン ///
	const string TITLE_SCENE_LAYOUT_JSON = "release/layouts/ui/titleScene_layout.json";
	const string TITLE_SCENE_START_BUTTON_NAME = "startButton";
	const string TITLE_SCENE_RANKING_BUTTON_NAME = "rankingButton";

	/// プレイシーン ///
	const string PLAY_SCENE_LAYOUT_JSON = "release/layouts/ui/playScene_layout.json";
	const string PLAY_SCENE_STAGE_LAYOUT_JSON = "Stage02.json";
	const string PLAY_SCENE_CAMERA_LAYOUT_JSON = "release/layouts/camera/tpsCamera_layout.json";
	const string PLAY_SCENE_TIMER_NAME = "timer";
}