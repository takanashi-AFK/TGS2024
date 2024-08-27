#pragma once

// �C���N���[�h�f�B���N�e�B�u
#include <string>
#include "../../../../../../Engine/Json/JsonReader.h"

// using�f�B���N�e�B�u
using std::string;

// �X�e�[�g�^�C�v
enum StateType
{
	Idle,
	Walk,
	None
};

class State
{
private:
	string name_;	// �X�e�[�g��(ID)
	StateType type_;	// �X�e�[�g�^�C�v

public:
	// �X�V
	State(string _name,StateType _type) :name_(_name),type_(_type){};
	
	// ������
	virtual void Initialize() = 0;
	
	// �J�n
	virtual void Start() = 0;
	
	// �X�V
	virtual void Update() = 0;

	virtual void Save(json& _saveObj){}
	virtual void Load(json& _loadObj){}

	void ChildSave(json& _saveObj);
	void ChildLoad(json& _loadObj);

	string GetName() const{ return name_; }
};

State* CreateState(string _name,StateType _type);
string StateTypeToString(StateType _type);