#include "State.h"

// インクルード
#include "State_Idle.h"

State* CreateState(string _name, StateType _type)
{
	switch (_type)
	{
	case Idle: return new State_Idle(_name);
	default: return nullptr;
	}
}

string StateTypeToString(StateType _type)
{
	switch (_type)
	{
	case Idle: return "Idle";
	case Walk: return "Walk";
	default: return "None";
	}
}

void State::ChildSave(json& _saveObj)
{
	_saveObj["name"] = name_;

	_saveObj["type"] = (int)type_;

	Save(_saveObj);
}

void State::ChildLoad(json& _loadObj)
{
	Load(_loadObj);
}
