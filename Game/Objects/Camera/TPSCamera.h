#pragma once
#include "../../../Engine/GameObject/GameObject.h"
#include "../../../Engine/Json/JsonReader.h"

class TPSCamera : public GameObject
{
private:
	XMFLOAT2 angle_;		// ��]�p�x
	float sensitivity_;		// ���x
	GameObject* pTarget_;	// �^�[�Q�b�g
	string targetName_;		// �^�[�Q�b�g��
	bool isActive_;			// �L������
	float targetHeight_;	// �J�����̍���
	float targetDistance_;	// �J�����̋���
	XMVECTOR prevAxis_;		// �O��̎�

public:
	/// <summary> �R���X�g���N�^ </summary>
	TPSCamera(GameObject* parent);

	/// <summary> ������ </summary>
	void Initialize() override;

	/// <summary> �X�V </summary>
	void Update() override;

	/// <summary> �`�� </summary>
	void Draw() override;

	/// <summary> ��� </summary>
	void Release() override;

	/// <summary>�@�ۑ� </summary>
	void Save(json& saveObj);

	/// <summary>�@�Ǎ� </summary>
	void Load(json& loadObj);

	/// <summary> ImGui�\�� </summary>
	void DrawData();

	/*
	setter :*/
	/// <summary> �J�����̗L�������̐ݒ� </summary>
	void SetActive(bool isActive) { isActive_ = isActive; }

	/// <summary> �J�����̊��x�̐ݒ� </summary>
	void SetSensitivity(float sensitivity) { sensitivity_ = sensitivity; }

	/// <summary> �J�����̍����̐ݒ� </summary>
	void SetTargetHeight(float targetHeight) { targetHeight_ = targetHeight; }

	/// <summary> �J�����̋����̐ݒ� </summary>
	void SetTargetDistance(float targetDistance) { targetDistance_ = targetDistance; }

	/// <summary> �^�[�Q�b�g�̐ݒ� </summary>
	void SetTarget(GameObject* target) { pTarget_ = target; }

	/// <summary> �^�[�Q�b�g���̐ݒ� </summary>
	void SetTargetName(string targetName) { targetName_ = targetName; }

	/// <summary> ��]�p�x�̐ݒ� </summary>
	void SetAngle(XMFLOAT2 angle) { angle_ = angle; }

	/*
	getter :*/
	/// <summary> �J�����̊��x�̎擾 </summary>
	float GetSensitivity() const { return sensitivity_; }

	/// <summary> �J�����̍����̎擾 </summary>
	float GetTargetHeight() const { return targetHeight_; }

	/// <summary> �J�����̋����̎擾 </summary>
	float GetTargetDistance() const { return targetDistance_; }

	/// <summary> �^�[�Q�b�g�̎擾 </summary>
	GameObject* GetTarget() const { return pTarget_; }

	/// <summary> �^�[�Q�b�g���̎擾 </summary>
	string GetTargetName() const { return targetName_; }

	/// <summary> ��]�p�x�̎擾 </summary>
	XMFLOAT2 GetAngle() const { return angle_; }

	/*
	predicate :*/
	/// <summary> �J�������L�����ǂ��� </summary>
	bool IsActive() const { return isActive_; }

	/// <summary> �^�[�Q�b�g���ݒ肳��Ă��邩�ǂ��� </summary>
	bool IsTarget() const { return pTarget_ != nullptr; }

private:
	/// <summary> ��]�p�x�̌v�Z </summary>
	void CalcRotateAngle(XMFLOAT3 _mouseMove, XMFLOAT3 _padMove);

	/// <summary> �J�����̈ʒu�ƒ����_�̌v�Z </summary>
	void CalcCameraPositionAndTarget(XMFLOAT3& _cameraPosition, XMFLOAT3& _camaraTarget);
};

