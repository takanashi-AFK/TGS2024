#pragma once

// インクルードディレクティブ
#include <string>

// usingディレクティブ
using std::string;

// ステートタイプ
enum StateType
{
	Idle,
	Walk,
	None
};

class State
{
private:
	string name_;	// ステート名(ID)
public:
	// 更新
	State(string _name) :name_(_name){};
	
	// 初期化
	virtual void Initialize() = 0;
	
	// 開始
	virtual void Start() = 0;
	
	// 更新
	virtual void Update() = 0;

	string GetName() const{ return name_; }
};

State* CreateState(string _name,StateType _type);
string StateTypeToString(StateType _type);