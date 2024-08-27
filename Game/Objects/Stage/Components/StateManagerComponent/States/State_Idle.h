#include "State.h"

class State_Idle : public State
{
public:
	// コンストラクタ
	State_Idle(string _name) :State(_name,StateType::Idle){};

	// 初期化
	void Initialize() override;

	// 開始
	void Start() override;

	// 更新
	void Update() override;
};
