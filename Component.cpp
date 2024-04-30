#include "Component.h"

Component::Component(StageObject* _holder, string _name)
    :holder_(_holder), name_(_name)
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
	this->Save(_saveObj);

	// 子コンポーネントの初期化
	for (auto comp : childComponents_)comp->ChildSave(_saveObj);
}

void Component::ChildDrawData()
{
	// 自身の情報を描画
	this->DrawData();

	// 子コンポーネントの情報を描画
	for (auto comp : childComponents_)comp->ChildDrawData();
}
