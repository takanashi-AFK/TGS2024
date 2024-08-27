#pragma once

// インクルードディレクティブ
#include <string>
#include "../../../../../../Engine/Json/JsonReader.h"

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
	StateType type_;	// ステートタイプ

public:
	// 更新
	State(string _name,StateType _type) :name_(_name),type_(_type){};
	
	// 初期化
	virtual void Initialize() = 0;
	
	// 開始
	virtual void Start() = 0;
	
	// 更新
	virtual void Update() = 0;

	virtual void Save(json& _saveObj){}
	virtual void Load(json& _loadObj){}

	void ChildSave(json& _saveObj);
	void ChildLoad(json& _loadObj);

	string GetName() const{ return name_; }
};

State* CreateState(string _name,StateType _type);
string StateTypeToString(StateType _type);