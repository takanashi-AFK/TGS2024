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
	friend class GameEditor;		// StageEditorクラスをフレンド宣言
	vector<StageObject*> objects_;	// 自身が保有するステージオブジェクト群

public:
	Stage(GameObject* _parent);

	void Initialize() override;

	void Update() override;

	void Draw() override;


};

