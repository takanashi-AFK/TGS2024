#pragma once
#include "../../../Engine/GameObject/GameObject.h"
#include "../../../Engine/Json/JsonReader.h"

class TPSCamera : public GameObject
{
private:
	XMFLOAT2 angle_;
	float sensitivity_;
	GameObject* pTarget_;
	string targetName_;
	bool isActive_;
	float targetHeight_;
	float targetDistance_;
	XMVECTOR prevAxis_;
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="parent">�e�I�u�W�F�N�g</param>
	TPSCamera(GameObject* parent);

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
	/// ���
	/// </summary>
	void Release() override;

	/// <summary>
	/// ImGui�\��
	/// </summary>
	void DrawData();

	/// <summary>
	/// �ۑ�
	/// </summary>
	/// <param name="saveObj">�ۑ��I�u�W�F�N�g</param>
	void Save(json& saveObj);

	/// <summary>
	/// �Ǎ�
	/// </summary>
	/// <param name="loadObj">�Ǎ��I�u�W�F�N�g</param>
	void Load(json& loadObj);

	/// <summary>
	/// ���s��Ԃ̐ݒ�
	/// </summary>
	/// <param name="isActive"></param>
	void SetActive(bool isActive) { isActive_ = isActive; }
	
	/// <summary>
	/// �ΏۃI�u�W�F�N�g�̐ݒ�
	/// </summary>
	/// <param name="target">�ΏۃI�u�W�F�N�g</param>
	void SetTarget(GameObject* target) { pTarget_ = target; }
	
	/// <summary>
	/// ��]�p�x�̎擾
	/// </summary>
	/// <returns>��]�p�x</returns>
	XMFLOAT2 GetAngle() { return angle_; }
};

