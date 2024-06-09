#pragma once
#include"../../Engine/GameObject/GameObject.h"

class Scene_Play:public GameObject
{
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

