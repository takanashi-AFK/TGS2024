#include "Component_Motion.h"

Component_Motion::Component_Motion(string _name, StageObject* _holder, ComponentType _type, Component* _parent)
 :Component(_holder, _name, _type, _parent)
{
}

void Component_Motion::Initialize()
{
}

void Component_Motion::Update()
{


}

void Component_Motion::Release()
{
}

void Component_Motion::DrawData()
{
}

void Component_Motion::PlayMotion(int _start, int _end, int _speed)
{
}
