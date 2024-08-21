#pragma once
#include "../State.h"
class PlayerState_Walk :
    public State
{
public:
	PlayerState_Walk(string name,StageObject* _holder);
	~PlayerState_Walk();

	void Initialize() override;
	void Start() override;
	void Update() override;
	void SetModel(string _filePath, int _animSpeed, int _animMaxFrame, int _animStartFrame) override;
};

