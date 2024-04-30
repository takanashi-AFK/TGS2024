#include "StageObject.h"

StageObject::StageObject(string _name, string _modelFilePath, GameObject* _parent)
	:GameObject(_parent,_name),modelFilePath_(_modelFilePath)
{
}

bool StageObject::AddComponent(Component* _comp)
{
	// エラー処理
	if (_comp == nullptr) 
	return false;

	// コンポーネントのvectorに追加する
	myComponents_.push_back(_comp); 
	return true;
}

bool StageObject::DeleteComponent(Component* _comp)
{
	// イテレータに、components_内で探したいデータを登録
	auto it = std::find(myComponents_.begin(), myComponents_.end(), _comp);

	//イテレータがリストの最後まで到達したら関数終了
	if (it == myComponents_.end()) 
	return false;

	//イテレータのコンポーネントを消す
	myComponents_.erase(it); 
	return true;
}

void StageObject::Initialize()
{
	// 保有するコンポーネントの初期化処理
	for (auto comp : myComponents_)
		comp->ChildIntialize();
}

void StageObject::Update()
{
	// 保有するコンポーネントの更新処理
	for (auto comp : myComponents_)
		comp->ChildUpdate();
}

StageObject* CreateStageObject(string _name, string _modelFilePath, GameObject* _parent)
{
	StageObject* obj = new StageObject(_name, _modelFilePath, _parent);
	obj->Initialize();
	if (_parent != nullptr)_parent->PushBackChild(obj);
	return obj;
}
