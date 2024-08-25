#pragma once

// �C���N���[�h�f�B���N�e�B�u
#include <string>

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
public:
	// �X�V
	State(string _name) :name_(_name){};
	
	// ������
	virtual void Initialize() = 0;
	
	// �J�n
	virtual void Start() = 0;
	
	// �X�V
	virtual void Update() = 0;

	string GetName() const{ return name_; }
};

State* CreateState(string _name,StateType _type);
string StateTypeToString(StateType _type);