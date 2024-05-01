#include "Stage.h"
#include "StageObject.h"

Stage::Stage(GameObject* _parent)
	:GameObject(_parent,"Stage")
{
}

void Stage::Initialize()
{
	CreateStageObject("object1", "DebugCollision/BoxCollider.fbx", this);
	CreateStageObject("object2", "DebugCollision/SphereCollider.fbx", this);
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
