#pragma once

// インクルード
#include <unordered_map>
#include "States/State.h"

using std::unordered_map;
class Component_StateManager;

class StageObject;

class StateObserver
{
public:
	// 初期化
	// クラスを継承した場合、必ず呼び出すこと
	bool Entry(StageObject* holder_);

	// ステート変更通知
	virtual void OnStateChange(Component_StateManager* _stateManager) = 0;
};

