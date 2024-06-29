#pragma once
#include "../../Engine/GameObject/GameObject.h"
class Scene_StageSelect: public GameObject
{
public:
	Scene_StageSelect(GameObject* parent);

	void Initialize() override;

	void Update() override;

	void Draw() override;

	void Release() override;
};

