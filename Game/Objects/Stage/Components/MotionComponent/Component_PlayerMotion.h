#pragma once
#include "Component_Motion.h"
#include <vector>
#include "../../Components/BehaviorComponents/Component_PlayerBehavior.h"

class Component_PlayerMotion : public Component_Motion
{
private:
	PlayerState state_;
	Component_PlayerBehavior* playerBehavior_;
	int animationEndFrame_ = 0;
	int currentFrame_ = 0;
	bool isAnimationEnd_ = false;
	int previousFrame_ = 0;
public:
	Component_PlayerMotion(string _name, StageObject* _holder, Component* _parent);
	void Initialize() override;
	void Update() override;
	void Release() override;
	void DrawData() override;

	bool IsEnd() const { return isAnimationEnd_; }

	int GetNowFrame();
};

