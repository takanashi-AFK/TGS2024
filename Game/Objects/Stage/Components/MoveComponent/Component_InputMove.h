#pragma once
#include "../Component.h"
#include "../StateManagerComponent/StateObserver.h"

class TPSCamera;

class Component_InputMove : public Component , StateObserver
{
private:
	bool isMove_;	// �ړ������ǂ���
	bool isEntryObserver_;	// �I�u�U�[�o�[�o�^�t���O
public:
	// �R���X�g���N�^
	Component_InputMove(string _name, StageObject* _holder, Component* _parent);

	// ������
	void Initialize() override;

	// �X�V
	void Update() override;

	// �X�V
	void Release() override;

	// �ۑ�
	void Save(json& _saveObj) override;

	// �Ǎ�
	void Load(json& _loadObj) override;

	// ImGui�p�l���\��
	void DrawData() override;

	// ��ԕύX�ʒm
	void OnStateChange(Component_StateManager* _stateManager) override;

private:
	void CalcDirection(XMVECTOR& dir);
	void CalcDirection(XMVECTOR& _dir, TPSCamera* _cam,bool _isYMove);
};

