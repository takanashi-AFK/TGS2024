#pragma once

// �C���N���[�h
#include <string>

// using�錾
using std::string;

// �t�@�C���p�X�̒萔���`
namespace Constants {

// �e��Json�t�@�C���̃p�X //////////////////////////////////////////////
	
	// UI���C�A�E�g
	const string SPLASH_SCENE_UI_LAYOUT_JSON = "Datas/UILayouts/splashScene_layout.json";
	const string TITLE_SCENE_UI_LAYOUT_JSON = "Datas/UILayouts/titleScene_layout.json";
	const string DIFFICULTY_SELECT_SCENE_UI_LAYOUT_JSON = "Datas/UILayouts/difficultySelectScene _layout.json";
	const string PLAY_SCENE_UI_LAYOUT_JSON = "Datas/UILayouts/playScene_layout.json";
	const string RESULT_SCENE_UI_LAYOUT_JSON = "Datas/UILayouts/resultScene_layout.json";
	const string END_SCENE_UI_LAYOUT_JSON = "Datas/UILayouts/endScene_layout.json";
	const string RANKING_SCENE_UI_LAYOUT_JSON = "Datas/UILayouts/rankingScene_layout.json";
	const string EASING_TEST_SCNE_LAYOUT_JSON = "Datas/UILayouts/test.json";

	// �X�e�[�W���C�A�E�g
	const string STAGE_EASY_JSON = "Datas/StageLayouts/stage_easy.json";
	const string STAGE_NORMAL_JSON = "Datas/StageLayouts/stage_normal.json";
	const string STAGE_HARD_JSON = "Datas/StageLayouts/stage_hard.json";
	const string STAGE_EXPERT_JSON = "Datas/StageLayouts/stage_expert.json";
	const string STAGE_INSANE_JSON = "Datas/StageLayouts/stage_insane.json";
	const string STAGE_BACKGROUND_JSON = "Datas/StageLayouts/resultStage.json";

	// �J�������C�A�E�g
	const string PLAY_SCENE_CAMERA_LAYOUT_JSON = "Datas/CameraLayouts/TPSCamera.json";
	const string TEST_SCENE_CAMERA_LAYOUT_JSON = "Datas/CameraLayouts/camera.json";

// �e��I�u�W�F�N�g�̖��O //////////////////////////////////////////////

	// �^�C�g���V�[���Ŏg�p����I�u�W�F�N�g��
	const string TITLE_SCENE_START_BUTTON_NAME = "startButton";
	const string TITLE_SCENE_RANKING_BUTTON_NAME = "rankingButton";
	const string TITLE_SCENE_USER_NAME_INPUT_NAME = "userNameInput";

	// ��Փx�I���V�[���Ŏg�p����I�u�W�F�N�g��
	const string DIFFICULTY_SELECT_SCENE_EASY_BUTTON_NAME = "easyButton";
	const string DIFFICULTY_SELECT_SCENE_NORMAL_BUTTON_NAME = "normalButton";
	const string DIFFICULTY_SELECT_SCENE_HARD_BUTTON_NAME = "hardButton";
	const string DIFFICULTY_SELECT_SCENE_EXPERT_BUTTON_NAME = "expertButton";

	// �v���C�V�[���Ŏg�p����I�u�W�F�N�g��
	const string PLAY_SCENE_TIMER_NAME = "timer";
	const string PLAY_SCENE_PLAYER_HP_GAUGE_NAME = "player_hpGauge";
	const string PLAY_SCENE_BOSS_HP_GAUGE_NAME = "boss_hpGauge";

	// ���U���g�V�[���Ŏg�p����I�u�W�F�N�g��
	const string RESULT_SCENE_HP_TEXT_NAME = "hpNum";
	const string RESULT_SCENE_TIME_TEXT_NAME = "timeNum";
	const string RESULT_SCENE_SCORE_TEXT_NAME = "scoreNum";
	const string RESULT_SCENE_NEXT_BUTTON_NAME = "nextButton";

	// �����L���O�V�[���Ŏg�p����I�u�W�F�N�g��
	const string RANKING_SCENE_RETURN_BUTTON_NAME = "returnButton";

// �e��fbx�t�@�C���̃p�X ///////////////////////////////////////////////

	/// �v���C���[�̃��[�V���� ///
	const string PLAYER_STATE_WALK_FBX = "Models/Player/Running.fbx";
	const string PLAYER_STATE_SHOOT_FBX = "Models/Player/Fireball.fbx";
	const string PLAYER_STATE_IDLE_FBX = "Models/Player/Silly Dancing.fbx";
	const string PLAYER_STATE_DODGE_FBX = "Models/Player/Female Action Pose.fbx";
	const string PLAYER_STATE_DEAD_FBX = "Models/Player/Standing React Death Right.fbx";

// �e��f�[�^�̃p�X ////////////////////////////////////////////////////

	// �����L���O�f�[�^
	const string RANKING_DATA_JSON = "Datas/ranking.json";

////////////////////////////////////////////////////////////////////////
}