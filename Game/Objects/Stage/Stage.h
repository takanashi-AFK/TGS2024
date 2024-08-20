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
	friend class GameEditor;		// StageEditor�N���X���t�����h�錾
	vector<StageObject*> objects_;	// ���g���ۗL����X�e�[�W�I�u�W�F�N�g�Q

public:
	Stage(GameObject* _parent);

	void Initialize() override;

	void Update() override;

	void Draw() override;


};

