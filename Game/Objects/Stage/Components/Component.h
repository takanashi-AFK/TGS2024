#pragma once

// �C���N���[�h
#include "../../../../Engine/Json/JsonReader.h"
#include "../../../../Engine/Collider/Collider.h"

// �O���錾
class StageObject;
class GameObject;


// using�錾
using std::vector;

// �R���|�[�l���g�^�C�v
enum ComponentType 
{
	BossBehavior,
	CactanBehavior,
	Chase,
	CircleRangeDetector,
	Fall,
	FanRangeDetector,
	HealthGauge,
	HelingoBehavior,
	HelingoFall,
	MeleeAttack,
	MoveX,
	PlayerBehavior,
	Rise,
	Rotation,
	RotationX,
	RotationY,
	RotationZ,
	ShootAttack,
	TackleMove,
	Timer,
	WASDInputMove,
	PlayerMotion,
	Teleporter,
	StateManager,
	// �R���|�[�l���g�ǉ����Ɏ��ʔԍ���ǉ�
	Max
	
};



// �R���|�\�l���g���N���X
class Component
{
protected:
	string name_;                           // �R���|�[�l���g��
	ComponentType type_;                    // �R���|�[�l���g�^�C�v
	StageObject* holder_;                   // �R���|�\�l���g�ۗL�҂̃|�C���^
	vector<Component*> childComponents_;    // �q�R���|�[�l���g�Q
	Component* parent_;                     // �e�R���|�[�l���g
	bool isActive_;                         // �A�N�e�B�u��Ԃ��ǂ���

public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="_holder">�ۗL��</param>
	/// <param name="_name">���O</param>
	Component(StageObject* _holder, string _name, ComponentType _type);
	Component(StageObject* _holder, string _name,ComponentType _type,Component* _parent);

	/// <summary>
	/// ������
	/// </summary>
	virtual void Initialize() = 0;

	/// <summary>
	/// �X�V
	/// </summary>
	virtual void Update() = 0;

	/// <summary>
	/// �J��
	/// </summary>
	virtual void Release() = 0;

	/// <summary>
	/// �Փˏ���
	/// </summary>
	virtual void OnCollision(GameObject* _target, Collider* _collider) {};

	/// <summary>
	/// �ۑ�
	/// </summary>
	/// <param name="_saveObj">�ۑ����</param>
	virtual void Save(json& _saveObj) {};

	/// <summary>
	/// �Ǎ�
	/// </summary>
	/// <param name="_saveObj">�Ǎ����</param>
	virtual void Load(json& _loadObj) {};

	/// <summary>
	/// ImGui�p�l���\��
	/// </summary>
	virtual void DrawData() {};

	/// <summary>
	/// ���g���q�R���|�[�l���g��������
	/// </summary>
	void ChildIntialize();

	/// <summary>
	/// ���g���q�R���|�[�l���g���X�V
	/// </summary>
	void ChildUpdate();

	/// <summary>
	/// ���g���q�R���|�[�l���g�����
	/// </summary>
	void ChildRelease();

	/// <summary>
	/// �Փˏ���
	/// </summary>
	void ChildOnCollision(GameObject* _target, Collider* _collider);

	/// <summary>
	/// ���g���q�R���|�[�l���g��`��
	/// </summary>
	void ChildDrawData();

	/// <summary>
	/// ���g���q�R���|�[�l���g��ۑ�
	/// </summary>
	void ChildSave(json& _saveObj);

	/// <summary>
	/// ���g���q�R���|�[�l���g��Ǎ�
	/// </summary>
	void ChildLoad(json& _loadObj);

	/// <summary>
	/// �q�R���|�[�l���g�����X�g�ɒǉ�
	/// </summary>
	/// <param name="comp">�R���|�[�l���g�^�C�v</param>
	bool AddChildComponent(Component* _comp);

	/// <summary>
	/// �q�R���|�[�l���g�����X�g����폜
	/// </summary>
	/// <param name="comp">�R���|�[�l���g�^�C�v</param>
	bool DeleteChildComponent(string _name);

	/// <summary>
	/// �R���|�[�l���g�����X�g�����邩�ɒT��
	/// </summary>
	/// <param name="_name">�R���|�[�l���g��</param>
	/// <returns>�R���|�[�l���g�����邩�ǂ���</returns>
	bool FindChildComponent(string _name);

	/// <returns>
	/// �q�R���|�[�l���g���擾
	/// </returns>
	/// <param name="_type">�R���|�[�l���g�^�C�v</param>
	Component* GetChildComponent(string _name);
	
	/// <returns>
	/// �q�R���|�[�l���g���擾
	/// </returns>
	vector<Component*> GetChildComponent(ComponentType _type);

	/// <returns>
	/// �R���|�[�l���g�^�C�v���擾
	/// </returns>
	ComponentType GetType() const { return type_; }

	/// <returns>
	/// �R���|�[�l���g�����擾
	/// </returns>
	string GetName() { return name_; }

	void Execute() { isActive_ = true; }
	void Stop() { isActive_ = false; }

	StageObject* GetHolder() { return holder_; }

};

/// <summary>
/// �R���|�[�l���g���쐬����
/// </summary>
/// <param name="_type">�R���|�[�l���g�^�C�v</param>
/// <param name="_holder">�ۗL��</param>
/// <returns>�쐬�����R���|�[�l���g</returns>
Component* CreateComponent(string _name,ComponentType _type,StageObject* _holder, Component* _parent);
Component* CreateComponent(string _name,ComponentType _type,StageObject* _holder);


/// <summary>
/// �R���|�[�l���g�^�C�v�𕶎���ɕϊ����� 
/// </summary>
string ComponentTypeToString(ComponentType _type);