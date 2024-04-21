#include "StageObject.h"

StageObject::StageObject()
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
	for (auto comp : myComponents_)
		comp->ChildIntialize();
}

void StageObject::Update()
{
	for (auto comp : myComponents_)
		comp->ChildUpdate();
}