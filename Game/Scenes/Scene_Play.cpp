#include "Scene_Play.h"

// �C���N���[�h
#include"../Objects/Stage/SkySphere.h"
#include"../Objects/Stage/Stage.h"
#include "../Objects/UI/UIPanel.h"
#include"../Objects/Stage/Components/GaugeComponents/Component_HealthGauge.h"
#include"../Objects/Stage/Components/BehaviorComponents/Component_PlayerBehavior.h"
#include"../../Engine/SceneManager.h"
#include "../Objects/UI/UIButton.h"
#include "../Objects/Camera/TPSCamera.h"
#include "../../Engine/ImGui/imgui.h"
#include "../../Engine/Global.h"
#include"../Manager/ScoreManager.h"



Scene_Play::Scene_Play(GameObject* parent)
{
}

void Scene_Play::Initialize()
{
	// �X�J�C�X�t�B�A�̐���
	SkySphere* skySphere = Instantiate<SkySphere>(this);

	// stageLayout_json�t�@�C����ǂݍ���
	json loadData;
	if (JsonReader::Load("Datas/StageLayouts/stage01_layout.json", loadData)) {

		// �X�e�[�W���쐬
		pStage_ = Instantiate<Stage>(this);
		pStage_->Load(loadData);
	}

	// �J�������̓ǂݍ���
	json camData;
	if (JsonReader::Load("Datas/CameraLayouts/TPSCamera.json", camData)) {

		TPSCamera* tpsCamera = Instantiate<TPSCamera>(this);
		tpsCamera->Load(camData);
	}

	pScore = new ScoreManager;

}

void Scene_Play::Update()
{
	// �V�[���ؑ֏���
	{
		bool isSceneChange = false;

		// �v���C���[�����񂾂�V�[����؂�ւ���
		{
			// �X�e�[�W���Ƀv���C���[�R���|�[�l���g�������Ă���L�����N�^�[�����݂��邩�ǂ����𔻒肵�擾
			vector<Component*> comp_playerBehaviors = pStage_->FindComponents(PlayerBehavior);

			// �͈�for���Ńv���C���[�R���|�[�l���g�̐����t���O���m�F
			for (auto comp : comp_playerBehaviors) {

				// �v���C���[�R���|�[�l���g������ł�����
				if (((Component_PlayerBehavior*)comp)->IsDead() == true) {

					pScore->AddScore(0);
					isSceneChange = true;
				}
			}
		}

		// �{�X�����񂾂�V�[����؂�ւ���
		{
			//// �X�e�[�W���Ƀ{�X�R���|�[�l���g�������Ă���L�����N�^�[�����݂��邩�ǂ����𔻒肵�擾
			//vector<Component*> comp_bossBehaviors = pStage_->FindComponents(BossBehavior);

			//// �͈�for���Ń{�X�R���|�[�l���g�̐����t���O���m�F
			//for (auto comp : comp_bossBehaviors) {

			//	// �{�X�R���|�[�l���g������ł�����
			//	if (((Component_BossBehavior*)comp)->IsDead() == true) {
			//		// �V�[����؂�ւ���
			//		SceneManager* sceneManager = (SceneManager*)FindObject("SceneManager");
			//		sceneManager->ChangeScene(SCENE_ID_END, TID_BLACKOUT);
			//	}
			//}
		}

		// debug
		{
			if (ImGui::Button("end")) {
				pScore->AddScore(200);
				isSceneChange = true;
			}
		}

		// �V�[���ؑ֏���
		if (isSceneChange) {
			// �V�[����؂�ւ���
			SceneManager* sceneManager = (SceneManager*)FindObject("SceneManager");
			sceneManager->ChangeScene(SCENE_ID_END, TID_BLACKOUT);
		}
	}
}

void Scene_Play::Draw()
{
}

void Scene_Play::Release()
{
}
