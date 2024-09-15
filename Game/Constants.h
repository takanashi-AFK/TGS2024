#pragma once

// �C���N���[�h
#include <string>

// using�錾
using std::string;

// �t�@�C���p�X�̒萔���`
namespace Constants {

	/// �X�v���b�V���V�[�� ///
	const string SPLASH_SCENE_LAYOUT_JSON = "Datas/UILayouts/splashScene_layout.json";

	/// �^�C�g���V�[�� ///
	const string TITLE_SCENE_LAYOUT_JSON = "Datas/UILayouts/titleScene_layout.json";
	const string TITLE_SCENE_START_BUTTON_NAME = "startButton";
	const string TITLE_SCENE_RANKING_BUTTON_NAME = "rankingButton";

	/// �v���C�V�[�� ///
	const string PLAY_SCENE_LAYOUT_JSON = "Datas/UILayouts/playScene_layout.json";
	const string PLAY_SCENE_STAGE_LAYOUT_JSON = "Stage02.json";
	const string PLAY_SCENE_CAMERA_LAYOUT_JSON = "Datas/CameraLayouts/TPSCamera.json";
	const string PLAY_SCENE_TIMER_NAME = "timer";
	const string PLAY_SCENE_PLAYER_HP_GAUGE_NAME = "player_hpGauge";
	const string PLAY_SCENE_BOSS_HP_GAUGE_NAME = "boss_hpGauge";

	/// ���U���g�V�[�� ///
	const string RESULT_SCENE_LAYOUT_JSON = "Datas/UILayouts/resultScene_layout.json";
	const string RESULT_SCENE_STAGE_LAYOUT_JSON = "Datas/StageLayouts/EndSceneStage.json";
	const string RESULT_SCENE_HP_TEXT_NAME = "hpNum";
	const string RESULT_SCENE_TIME_TEXT_NAME = "timeNum";
	const string RESULT_SCENE_SCORE_TEXT_NAME = "scoreNum";
	const string RESULT_SCENE_NEXT_BUTTON_NAME = "nextButton";

	/// �G���h�V�[�� ///
	const string END_SCENE_LAYOUT_JSON = "Datas/UILayouts/endScene_layout.json";

	/// �����L���O�V�[�� ///
	const string RANKING_SCENE_LAYOUT_JSON = "Datas/UILayouts/rankingScene_layout.json";
	const string RANKING_SCENE_RETURN_BUTTON_NAME = "returnButton";

	/// �e�X�g�V�[�� ///
	const string TEST_SCENE_CAMERA_LAYOUT_JSON = "Datas/CameraLayouts/camera.json";

	// �f�[�^
	const string RANKING_DATA_CSV = "ranking.csv";

}