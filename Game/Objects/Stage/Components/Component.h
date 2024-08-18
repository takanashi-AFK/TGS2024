#pragma once

#include "../../../../Engine/Json/JsonReader.h"
#include "../../../../Engine/Collider/Collider.h"
#include<vector>

using std::vector;

class StageObject;

enum ComponentType
{
	Max
};


class Component
{
protected:
	string componentname_;//コンポーネントの名前
	ComponentType compType_;
	StageObject* holder_;
	vector<Component*>childComponent_;
	Component* compParent_;
	bool isActive_;
public:

	Component(StageObject* _holder, string _name, ComponentType _compType, Component* _compParent);
	Component(StageObject* _holder, string _name, ComponentType _compType);

	virtual void Initialize() = 0;

	virtual void Update() = 0;

	virtual void Release() = 0;

	virtual void OnCollision(GameObject* _target, Collider* _collider);

	virtual void Save(json& _saveObj);

	virtual void Load(json& _loadObj);

	virtual void DrawImgui();

	void ChildInitialize();

	void ChildUpdate();

	virtual void ChildRelease();

	virtual void ChildOnCollision(GameObject* _childtarget, Collider* _childcollider);

	virtual void ChildSave(json& _childsaveObj);

	virtual void ChildLoad(json& _childloadObj);

	virtual void ChildDrawImgui();

	bool AddChildComponent(Component* _childComp);

	bool DeleteChildComponent(string _childComp);

	bool FindChildComponent(string _childComp);

	Component* GetChildComponent(string _compname);

	vector<Component*>GetChildComponent(ComponentType _comptype);

	ComponentType GetType() { return compType_; }

	string GetName() { return componentname_; }

	void Execute() { isActive_ = true; }
	void Stop() { isActive_ = false; }
};
Component* CreateComponent(string _name, ComponentType _type, StageObject* _holder, Component* _parent);
Component* CreateComponent(string _name, ComponentType _type, StageObject* _holder);

string ComponentTypeToString(ComponentType _comptype);