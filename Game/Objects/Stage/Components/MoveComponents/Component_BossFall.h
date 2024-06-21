#pragma once
#include "../Component.h"
class Component_BossFall :public Component
{
private:
	enum STATE { FALL, RISE, WAIT, };	// èÛë‘
	STATE nowState_;	// åªç›ÇÃèÛë‘
	STATE prevState_;	
	bool isActive_;
	bool isEnd_;
public:
	Component_BossFall(string _name, StageObject* _holder, Component* _parent);
	void Initialize() override;
	void Update() override;
	void Release() override;
	void Save(json& _saveObj) override;
	void Load(json& _loadObj) override;
	void DrawData() override;

	void SetState(STATE _state) { nowState_ = _state; }

	void Stop() { isActive_ = false;  }
	void Execute() { isActive_ = true; }

	bool GetIsEnd() { return isEnd_; }
	void SetIsEnd(bool _isEnd) { isEnd_ = _isEnd; }
	void Wait();
};

