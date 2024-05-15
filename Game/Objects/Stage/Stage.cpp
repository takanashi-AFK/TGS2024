#include "Stage.h"

// インクルード
#include "StageObject.h"

#include "../Stage/Components/ChaseComponents/Component_Chase.h"

Stage::Stage(GameObject* _parent)
	:GameObject(_parent,"Stage"),objects_()
{
}

void Stage::Initialize()
{
	// 対象オブジェクトを生成
	StageObject* tbj = CreateStageObject("TargetObject", "Models/DebugCollision/BoxCollider.fbx", this);

	// デバッグ用のオブジェクトを生成
	StageObject* obj = CreateStageObject("StageObject", "Models/DebugCollision/SphereCollider.fbx", this);
	
	Component* comp = CreateComponent(Chase, obj);
	((Component_Chase*)comp)->SetTarget(tbj);

	obj->AddComponent(comp);
	AddStageObject(obj);
	AddStageObject(tbj);


}

void Stage::Update()
{
}

void Stage::Draw()
{
}

void Stage::Release()
{
}

void Stage::Save(json& _saveObj)
{
	// オブジェクト群を保存
	for (auto obj : objects_)obj->Save(_saveObj[obj->GetObjectName()]);
}

void Stage::Load(json& _loadObj)
{
	// ステージオブジェクトをすべて削除
	DeleteAllStageObject();

	for (auto it = _loadObj.begin(); it != _loadObj.end();++it) {
		
		// オブジェクトのインスタンスを生成
		StageObject* obj = CreateStageObject(it.key(), it.value()["modelFilePath_"], this);
		
		// オブジェクト情報を読込
		obj->Load(it.value());

		// オブジェクトをリストに追加
		AddStageObject(obj);
	}
}

void Stage::DrawData()
{
	for (auto obj : objects_)obj->DrawData();
}

void Stage::AddStageObject(StageObject* _obj)
{
	// リストに追加
	if (_obj != nullptr)objects_.push_back(_obj);
}

void Stage::DeleteStageObject(StageObject* _obj)
{
	// オブジェクトを削除する
	_obj->KillMe();

	// オブジェクトのイテレータを取得する
	auto it = std::find(objects_.begin(), objects_.end(), _obj);

	// イテレータが見つかった場合、ベクターから削除する
	if (it != objects_.end()) objects_.erase(it);
}

void Stage::DeleteAllStageObject()
{
	// リスト内にある要素をすべて削除
	for (auto obj : objects_) obj->KillMe();
	objects_.clear();
}
