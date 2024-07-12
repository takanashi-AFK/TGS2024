#pragma once

//�C���N���[�h
#include "../Component.h"
#include "../../StageObject.h"
#include "../DetectorComponents/Component_CircleRangeDetector.h"
#include "../../../../../EffekseeLib/EffekseerVFX.h"
#include "../MoveComponents/Component_WASDInputMove.h"
#include <DirectXMath.h>
#include <string>
using namespace DirectX;
class Component_Teleporter : public Component
{
private:
	enum TELEPORTERSTATE
	{
		TELEPORTSTART,
		TELEPORTING,
		TELEPORTEND,
	};
	TELEPORTERSTATE teleportState_;

	float scaleValue_;
	float lowerLimit_;
	float default_;
	StageObject* target_;
	string targetName_;
	XMFLOAT3 teleportPosition_; // �e���|�[�g��̍��W
	Component_WASDInputMove* move_;
	// effekseer: �ό`�s��
	std::shared_ptr<EFFEKSEERLIB::EFKTransform> mt;/*������*/
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

	void TeleportStart();
	void Teleporting();
	void TeleportEnd();

};