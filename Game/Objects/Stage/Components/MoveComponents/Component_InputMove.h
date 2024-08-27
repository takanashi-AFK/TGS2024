#pragma once
#include "../Component.h"
#include "../StateComponents/StateObserver.h"
#include "../StateComponents/Component_StateManager.h"


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
};
