#include "Component.h"

#include "RotationYComponent.h"

Component::Component(StageObject* _holder, string _name,ComponentType _type)
    :holder_(_holder), name_(_name),type_(_type)
{
}

void Component::ChildIntialize()
{
	// 自身の初期化
	this->Initialize();

	// 子コンポーネントの初期化
	for (auto comp : childComponents_)comp->ChildIntialize();
}

void Component::ChildUpdate()
{
	// 自身の更新
	this->Update();

	// 子コンポーネントの更新
	for (auto comp : childComponents_)comp->ChildUpdate();
}

void Component::ChildRelease()
{
	// 子コンポーネントの開放
	for (auto comp : childComponents_) comp->ChildRelease();
	childComponents_.clear();
	
	// 自身の開放
	this->Release();
}

void Component::ChildSave(json& _saveObj)
{
	// 自身の保存
	this->Save(_saveObj[this->type_]);

	// 子コンポーネントの初期化
	for (auto comp : childComponents_)comp->ChildSave(_saveObj["childComponents_"]);
}

void Component::ChildLoad(json& _loadObj)
{
	// 自身の読込
	this->Load(_loadObj);

	// 自身のコンポーネントを読込
	for (auto it = _loadObj["childComponents_"].begin(); it != _loadObj["childComponents_"].end(); ++it) LoadComponent(holder_,(ComponentType)std::stoi(it.key()), it.value());
}

void Component::ChildDrawData()
{
	// 自身の情報を描画
	this->DrawData();

	// 子コンポーネントの情報を描画
	for (auto comp : childComponents_)comp->ChildDrawData();
}

Component* LoadComponent(StageObject* _holder,ComponentType _type, json& _loadObj)
{
	// コンポーネントを生成
	Component* comp = nullptr;
	switch (_type){
	case RotationY: new RotationYComponent(_holder);
	}

	// コンポーネントに必要な情報を読込
	comp->Load(_loadObj);
	return comp;
}
