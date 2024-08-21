#pragma once

// �C���N���[�h
#include "../../../Engine/GameObject/GameObject.h"
#include "Components/Component.h"
#include <vector>

// using�錾
using std::vector;

enum AttributeType {
	ENEMY,
	ATMAX
};
/// <summary>
/// �X�e�[�W�ɓo�ꂷ��I�u�W�F�N�g�̃N���X
/// </summary>
class StageObject : public GameObject
{
protected:
	vector<Component*> myComponents_;   // ���g���ۗL����R���|�[�l���g�Q
	string modelFilePath_;              // ���f���̃t�@�C���p�X
	int modelHandle_;                   // ���f���ԍ�
	AttributeType attribute_;           // ����
	bool isOnGround_;                   // �n�ʂɐݒu���邩�ǂ���
	bool isCollisionWall_;              // �ǂɓ����������ǂ���
	float fallSpeed_;                   // �������x

	bool isShadeVisible_;               // �A�̕\��
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="_name">�I�u�W�F�N�g��</param>
	/// <param name="_modelFilePath">���f���t�@�C���p�X</param>
	/// <param name="_parent">�e�I�u�W�F�N�g</param>
	StageObject(string _name,string _modelFilePath,GameObject* _parent);

	/// <summary>
	/// ������
	/// </summary>
	void Initialize() override;

	/// <summary>
	/// �X�V
	/// </summary>
	void Update() override;

	/// <summary>
	/// �`��
	/// </summary>
	void Draw() override;

	/// <summary>
	/// �J��
	/// </summary>
	void Release() override;

	/// <summary>
	/// �Փˏ���
	/// </summary>
	void OnCollision(GameObject* _target, Collider* _collider) override;

	/// <summary>
	/// �ۑ�
	/// </summary>
	/// <param name="_saveObj">�ۑ��f�[�^</param>
	virtual void Save(json& _saveObj);

	/// <summary>
	/// �Ǎ�
	/// </summary>
	/// <param name="_loadObj">�Ǎ��f�[�^</param>
	virtual  void Load(json& _loadObj);

	/// <summary>
	/// ImGui�p�l���\��
	/// </summary>
	virtual void DrawData();

	/// <summary>
	/// �R���|�[�l���g�����X�g�ɒǉ�
	/// </summary>
	/// <param name="_comp">�ǉ�����R���|�[�l���g</param>
	/// <returns>�ǉ��ł������ǂ���</returns>
	bool AddComponent(Component* _comp);

	/// <summary>
	/// �R���|�[�l���g�����X�g����T��
	/// </summary>
	Component* FindComponent(string _name);

	/// <summary>
	/// �R���|�[�l���g�����X�g����T��
	/// </summary>
	vector<Component*> FindComponent(ComponentType _type);

	/// <summary>
	/// �R���|�[�l���g�����X�g����폜
	/// </summary>
	/// <param name="_comp">�폜����R���|�[�l���g</param>
	/// <returns>�폜�ł������ǂ���</returns>
	bool DeleteComponent(Component* _comp);

	/// <summary>
	/// �R���|�[�l���g�����X�g����S�č폜
	/// </summary>
	/// <returns>�폜�ł������ǂ���</returns>
	bool DeleteAllComponent();

	/// <summary>
	/// �����̃Z�b�g
	/// </summary>
	/// <param name="_type">AttributeType</param>
	void SetAttribute(AttributeType _type) { attribute_ = _type; }

	/// <summary>
	/// �����̃Q�b�^�[
	/// </summary>
	/// <returns></returns>
	AttributeType GetAttribute() { return attribute_; }

	/// <summary>
	/// ���f���ԍ��̎擾
	/// </summary>
	/// <returns>���f���ԍ�</returns>
	int GetModelHandle() { return modelHandle_; }

	/// <summary>
	/// �ڒn����
	/// </summary>
	/// <param name="_fallSpeed">�������x</param>
	void OnGround(float _fallSpeed);

	/// <summary>
	/// �ǂ߂荞�ݖh�~����
	/// </summary>
	void CollisionWall();

	void PlayAnimation(int _start, int _end, float _speed);

	void SetModelHandle(int _handle) { modelHandle_ = _handle; }

	string GetModelFilePath() { return modelFilePath_; }

};

/// <summary>
/// �X�e�[�W�I�u�W�F�N�g�𐶐�����֐�
/// </summary>
/// <param name="_name"> �I�u�W�F�N�g��</param>
/// <param name="_modelFilePath"> ���f���t�@�C���p�X</param>
/// <param name="_parent"> �e�I�u�W�F�N�g</param>
/// <returns>�쐬�����I�u�W�F�N�g�̃|�C���^</returns>
StageObject* CreateStageObject(string _name, string _modelFilePath, GameObject* _parent);