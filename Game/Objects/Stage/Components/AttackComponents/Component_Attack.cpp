#include "Component_Attack.h"

Component_Attack::Component_Attack(StageObject* _holder, string _name, ComponentType _type,Component* _parent) :
	Component(_holder, _name, _type,_parent), isAttack_(false), power_(0)
{
}
