#pragma once
#include "../../Engine/GameObject/GameObject.h"

class  UIPanel;
class UIButton;
#include <vector>
class Scene_StageSelect: public GameObject
{

private:
	UIPanel* uipanel;//UI�p�l���̃|�C���^�ϐ�
	std::vector<UIButton*>stageImages;
	int StageIndex;
	bool isRightButtonMoving_;//�{�^�����E�����ɓ����Ă邩�ǂ���
	bool isLeftSelectButtonMoving_;//-�����ɓ����Ă��邩�ǂ���
	float moveselectButton;//�{�^���𓮂������߂̊���
	std::string easingfunc_;//���[����

public:
	Scene_StageSelect(GameObject* parent);

	void Initialize() override;

	void Update() override;

	void Draw() override;

	void Release() override;

private:
	/// <summary>
	/// �{�^�����E�ɓ����֐�
	/// </summary>
	void RightButtonMoving();

	/// <summary>
	/// �{�^�������ɓ����֐�
	/// </summary>
	void LeftButtonMoving();

	void MoveButtons(bool _moving);
};

