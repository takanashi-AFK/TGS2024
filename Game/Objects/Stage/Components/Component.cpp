#include "Component.h"
#include"../../../../Engine/ImGui/imgui.h"
#include"../StageObject.h"

Component::Component(StageObject* _holder, string _name, ComponentType _compType, Component* _compParent)
{
}

Component::Component(StageObject* _holder, string _name, ComponentType _compType)
{
}

void Component::ChildInitialize()
{
}

void Component::ChildUpdate()
{
}

void Component::ChildRelease()
{
}

void Component::ChildOnCollision(GameObject* _childtarget, Collider* _childcollider)
{
}

void Component::ChildSave(json& _childsaveObj)
{
}

void Component::ChildLoad(json& _childloadObj)
{
}

void Component::ChildDrawImgui()
{
}

bool Component::AddChildComponent(Component* _childComp)
{
	return false;
}

bool Component::DeleteChildComponent(string _childComp)
{
	return false;
}

bool Component::FindChildComponent(string _childComp)
{
	return false;
}

Component* Component::GetChildComponent(string _compname)
{
	return nullptr;
}

vector<Component*> Component::GetChildComponent(ComponentType _comptype)
{
	return vector<Component*>();
}

Component* CreateComponent(string _name, ComponentType _type, StageObject* _holder, Component* _parent)
{
	return nullptr;
}

Component* CreateComponent(string _name, ComponentType _type, StageObject* _holder)
{
	return nullptr;
}

string ComponentTypeToString(ComponentType _comptype)
{
	return string();
}
