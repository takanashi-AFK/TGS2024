#pragma once
#include"../../Engine/GameObject/GameObject.h"

class Component_HealthManager;

class Scene_Play:public GameObject
{
	Component_HealthManager* health_;

public:

	Scene_Play(GameObject* parent);
	//‰Šú‰»
	void Initialize() override;

	//XV
	void Update() override;

	//•`‰æ
	void Draw() override;

	//ŠJ•ú
	void Release() override;
};

