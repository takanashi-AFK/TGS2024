#include "State.h"

class State_Idle : public State
{
public:
	// �R���X�g���N�^
	State_Idle(string _name) :State(_name){};

	// ������
	void Initialize() override;

	// �J�n
	void Start() override;

	// �X�V
	void Update() override;
};
