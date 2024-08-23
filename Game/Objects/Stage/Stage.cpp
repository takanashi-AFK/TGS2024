#include "Stage.h"
#include"../../../Engine/GameObject/GameObject.h"
#include"StageObject.h"
Stage::Stage(GameObject* _parent)
	:GameObject(_parent, "Stage"), objects_()
{
}

void Stage::Initialize()
{
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
}

void Stage::load(json& _loadObj)
{
}

void Stage::AddStageObject(StageObject* _stageObj)
{
	if (_stageObj != nullptr)objects_.push_back(_stageObj);
}

void Stage::DeleateStageObject(StageObject* _stageObj)
{
	auto it = std::find(objects_.begin(), objects_.end(), _stageObj);

	if (it != objects_.end())objects_.erase(it);

	_stageObj->KillMe();
}

void Stage::AllDeleateStageObject()
{
	for (auto obj : objects_)obj->KillMe();

	objects_.clear();
}

StageObject* Stage::GetStageObject(string _name)
{
	for (auto obj : objects_) {
		if (obj->GetObjectName() == _name)return obj;
	}

	return nullptr;
}

