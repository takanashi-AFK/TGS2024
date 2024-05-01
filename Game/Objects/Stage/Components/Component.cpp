#include "Component.h"
#include "../StageObject.h"

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

void Component::ChildDrawData()
{
	// 自身の情報を描画
	this->DrawData();

	// 子コンポーネントの情報を描画
	for (auto comp : childComponents_)comp->ChildDrawData();
}

void Component::ChildSave(json& _saveObj)
{
	// 自身の情報を保存
	this->Save(_saveObj);

	// 子コンポーネントの情報を保存
	for (auto comp : childComponents_)comp->Save(_saveObj["childComponents_"][comp->GetName()]);
}

void Component::ChildLoad(json& _loadObj)
{
	// 自身の情報を保存
	this->Load(_loadObj);

	// 子コンポーネントの情報を読込
	for (auto comp : childComponents_)comp->Load(_loadObj["childComponents_"][comp->GetName()]);
}

bool Component::AddChildComponent(Component* _comp)
{
	// ヌルチェック
	if (_comp == nullptr)
		return false;

	// 初期化
	_comp->ChildIntialize();

	// コンポーネントのリストに追加する
	childComponents_.push_back(_comp);
	return true;
}

bool Component::DeleteChildComponent(Component* _comp)
{
	// イテレータに、"childComponents_"内で探したいデータを登録
	auto it = std::find(childComponents_.begin(), childComponents_.end(), _comp);

	// イテレータがリストの最後まで到達したら関数終了
	if (it == childComponents_.end())
		return false;

	// イテレータのコンポーネントを消す
	childComponents_.erase(it);
	return true;
}

Component* CreateComponent(ComponentType _type, StageObject* _holder)
{
	Component* comp = nullptr;

	// タイプ(識別番号にしたがってコンポーネントを作成)
	switch (_type)
	{
	case RotationY:comp = new RotationYComponent(_holder);break;
	}
	return comp;
}
