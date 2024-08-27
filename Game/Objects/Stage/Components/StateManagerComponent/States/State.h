#pragma once

// �C���N���[�h�f�B���N�e�B�u
#include <string>
#include <vector>
#include "../../../../../../Engine/Json/JsonReader.h"

// using�f�B���N�e�B�u
using std::string;
using std::vector;

// �O�v�錾
class StageObject;

// �X�e�[�g�^�C�v
enum StateType
{
	Idle,
	Walk,
	None
};

class State
{
protected:
	string name_;	// �X�e�[�g��(ID)
	StateType type_;	// �X�e�[�g�^�C�v
	StageObject* holder_;	// �X�e�[�g�����I�u�W�F�N�g

	struct ModelData {
		string filePath;
		int modelHandle;

		int animFrameMax;
		int animFrameStart;
		float animSpeed;

		void Load();
	};
	vector<ModelData> modelDataList_;	// ���f���f�[�^���X�g

public:
	// �X�V
	State(string _name,StateType _type,StageObject* _holder) :name_(_name),type_(_type),holder_(_holder){};
	
	// ������
	virtual void Initialize() = 0;
	
	// �J�n
	virtual void Start() = 0;
	
	// �X�V
	virtual void Update() = 0;

	virtual void Save(json& _saveObj){}
	virtual void Load(json& _loadObj){}
	void DrawData(){}

	void ChildSave(json& _saveObj);
	void ChildLoad(json& _loadObj);
	void ChildDrawData();

	string GetName() const{ return name_; }
	StateType GetType() const { return type_; }
	StageObject* GetHolder() const { return holder_; }

	void AddModelData(string _filePath,int _animFrameMax,int _animFrameStart,float _animSpeed);	

private:
	bool isAddModelWindowOpen_;	// ���f���ǉ��E�B���h�E�\���t���O
	void DrawAddModelWindow();
};

State* CreateState(string _name,StateType _type,StageObject* _holder);
string StateTypeToString(StateType _type);