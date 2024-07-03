#pragma once
#include "global.h"
#include "GameObject/GameObject.h"
#include "ResourceManager/Transition.h"

//�Q�[���ɓo�ꂷ��V�[��
enum SCENE_ID
{
	SCENE_ID_TEST = 0,
	SCENE_ID_SPLASH,
	SCENE_ID_TITLE,
	SCENE_ID_PLAY,
	SCENE_ID_STAGESELECT,
	SCENE_ID_END
};


//-----------------------------------------------------------
//�V�[���؂�ւ���S������I�u�W�F�N�g
//-----------------------------------------------------------
class SceneManager : public GameObject
{
public:

	//�R���X�g���N�^
	//�����Fparent	�e�I�u�W�F�N�g�i��{�I�ɃQ�[���}�l�[�W���[�j
	SceneManager(GameObject* parent);

	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;

	//�V�[���؂�ւ��i���ۂɐ؂�ւ��̂͂��̎��̃t���[���j
	//�����Fnext	���̃V�[����ID
	//�����Ftype	�g�����W�V����ID
	//�����Ftime	����(�b)
	void ChangeScene(SCENE_ID next, TRANSITION_ID _type, float _time);
	void ChangeScene(SCENE_ID next, TRANSITION_ID _type);
	void ChangeScene(SCENE_ID next);

private:

	SCENE_ID currentSceneID_;	//���݂̃V�[��
	SCENE_ID nextSceneID_;		//���̃V�[��
	SCENE_ID tmpID_;
};