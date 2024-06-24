#pragma once
#include "StageObject.h"
class Knuckle :public StageObject
{
private:
	int frame_;
	bool isEnd_;
	Component* move_;
public:
	Knuckle(GameObject* _parent);
	void Initialize() override;
	void Update() override;
	void Release() override;
	void Draw() override;
	void AutoDelete(float _sec);
	bool IsEnd() { return isEnd_; }
};

