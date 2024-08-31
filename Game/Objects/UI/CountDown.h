#pragma once
#include "../../../Engine/GameObject/GameObject.h"
#include<vector>
class CountDown :
    public GameObject
{
private:
	std::vector<int> countDownImages_;
	bool isCountDown_;
public:
	CountDown(GameObject* _parent);
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;

	bool GetIsCountDown() { return isCountDown_; }

};

