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
