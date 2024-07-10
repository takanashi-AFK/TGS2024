#pragma once

//�C���N���[�h
#include "../Component.h"
#include "../../StageObject.h"
#include <string>
class Component_Teleporter : public Component
{
private:
	StageObject* target_;
	string targetName_;
	XMFLOAT3 teleportPosition_; // �e���|�[�g��̍��W
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="_holder">�ۗL��</param>
	Component_Teleporter(string _name, StageObject* _holder, Component* _parent);

	/// <summary>
	/// ������
	/// </summary>
	void Initialize() override;

	/// <summary>
	/// �X�V
	/// </summary>
	void Update() override;

	/// <summary>
	/// �J��
	/// </summary>
	void Release() override;

	/// <summary>
	/// �ۑ�
	/// </summary>
	/// <param name="_saveObj">�ۑ����</param>
	void Save(json& _saveObj) override;

	/// <summary>
	/// �Ǎ�
	/// </summary>
	/// <param name="_loadObj">�Ǎ����</param>
	void Load(json& _loadObj) override;

	/// <summary>
	/// ImGui�p�l���\��
	/// </summary>
	void DrawData() override;

	/// <summary>
   /// �Փˏ���
   /// </summary>
   /// <param name="_target">�ՓˑΏ�</param>
	void Teleport(GameObject* _target);

	/// <summary>
	/// �e���|�[�g���ݒ�
	/// </summary>
	/// <param name="position">�e���|�[�g��̍��W</param>
	void SetTeleportPosition(const XMFLOAT3& position);
};