#pragma once

#include "../../../Engine/GameObject/GameObject.h"
#include "Components/Component.h"

#include "../../../Engine/Json/JsonReader.h"
#include <vector>

using std::vector;

class StageObject;

class Stage :public GameObject
{
private:
	//friend class GameEditor;		// StageEditorクラスをフレンド宣言
	vector<StageObject*> objects_;	// 

public:
	Stage(GameObject* _parent);

	void Initialize() override;

	void Update() override;

	void Draw() override;

	void Release() override;

	void Save(json& _saveObj);

	void load(json& _loadObj);

	void AddStageObject(StageObject* _stageObj);

	void DeleateStageObject(StageObject* _stageObj);

	void AllDeleateStageObject();

	vector<StageObject*>& GetStageObjects() { return objects_; }

	StageObject* GetStageObject(string _name);
};

