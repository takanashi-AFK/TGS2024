#pragma once
#include <vector>
#include "../../../Engine/Json/JsonReader.h"
#include "../../../../../Engine/GameObject/Transform.h"
#include "../../../../../Engine/Collider/BoxCollider.h"
#include "../../../../../Engine/Collider/SphereCollider.h"


using std::vector;

enum UIType {
	UI_NONE,
	UI_BUTTON,
	UI_IMAGE,
	UI_TEXT,
	UI_PANEL,
	UI_MAX,
};

class UIObject
{
private:
	bool isPositionLocked_;
	bool isRotateLocked_;
	bool isScaleLocked_;

protected:
	std::string objectName_; // �I�u�W�F�N�g��
	Transform transform_; // �ʒu������Ȃǂ��Ǘ�����I�u�W�F�N�g
	bool isEnable_;	// �L�����ǂ���
	UIType type_;	// UI�̎��
	int layerNumber_; // ���C���[�ԍ�
	std::vector<UIObject*> childList_;  // �q�I�u�W�F�N�g�̃��X�g
	UIObject* pParent_;// �e�I�u�W�F�N�g

	//�t���O
	struct UI_STATE
	{
		unsigned initialized : 1;	//�������ς݂�
		unsigned entered : 1;		//�X�V���邩
		unsigned visible : 1;		//�`�悷�邩
		unsigned dead : 1;			//�폜���邩
	};
	UI_STATE state_;

public:

	//�R���X�g���N�^
	UIObject();
	UIObject(UIObject* parent);
	UIObject(string _name, UIType _type, UIObject* parent, int _layerNum);

	//�f�X�g���N�^
	virtual ~UIObject();

	//�e�I�u�W�F�N�g�ŕK�����֐�
	virtual void Initialize() {};
	virtual void Update() {};
	virtual void Draw() {};
	virtual void Release() {};

	//�����̊Y���֐���ǂ񂾌�A�q���̊֐����Ă�
	void UpdateSub();
	void DrawSub();
	void ReleaseSub();

	bool IsDead(); //�폜���邩�ǂ���


	virtual void Save(json& saveObj) {};
	virtual void Load(json& loadObj) {};
	virtual void DrawData() {};
	  
	void ChildSave(json& _saveObj);
	void ChildLoad(json& _loadObj);
	void ChildDrawData();

	void LockPosition() { isPositionLocked_ = true; }
	void LockRotate() { isRotateLocked_ = true; }
	void LockScale() { isScaleLocked_ = true; }

	void UnlockPosition() { isPositionLocked_ = false; }
	void UnlockRotate() { isRotateLocked_ = false; }
	void UnlockScale() { isScaleLocked_ = false; }

	void KillMe();	// �������폜����

	//���O�ŃI�u�W�F�N�g�������i�Ώۂ͎����̎q���ȉ��j
	//�����Fname	�������閼�O
	//�ߒl�F�������I�u�W�F�N�g�̃A�h���X�i������Ȃ����nullptr�j
	UIObject* FindChildObject(const std::string& name);
	UIObject* FindObject(const std::string& name){ return GetRootJob()->FindChildObject(name); }


	//�I�u�W�F�N�g�̖��O���擾
	//�ߒl�F���O
	const std::string& GetObjectName(void) const;

	//Root�I�u�W�F�N�g���擾(UIPanel)
	UIObject* GetRootJob();

	//�e�I�u�W�F�N�g���擾
	UIObject* GetParent();

	/// <summary>
	/// �q�I�u�W�F�N�g��ǉ�(���X�g�̍Ō��)
	/// </summary>
	/// <param name="obj"></param>
	void PushBackChild(UIObject* obj);

	/// <summary>
	/// �V�������C���[�ԍ���ݒ�
	/// </summary>
	/// <param name="newLayerNumber_">�V�������C���[�ԍ�</param>
	void SetLayerNumber(int newLayerNumber_);
	// Getter
	int GetLayerNumber() { return layerNumber_; }

	/// <summary>
	/// ���C���[���d�����Ă��邩�ǂ���
	/// </summary>
	/// <param name="newLayerNumber_"></param>
	/// <returns></returns>
	bool IsLayerNumberDuplicate(int newLayerNumber_);

	//�I�u�W�F�N�g�����C���[�ԍ��Ŕ�r���邽�߂̊֐�
	static bool CompareLayerNumber(UIObject* _object1, UIObject* _object2);

};

UIObject* CreateUIObject(string _name, UIType _type, UIObject* _parent, int _layerNum);
string GetUITypeString(UIType _type);

