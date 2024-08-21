// �O���錾
#include <string>
class StageObject;
using std::string;
// ��Ԃ̓��� ���N���X
class State
{
protected:
	string name_;  // ��Ԗ�
	StageObject* holder_;  // �ۗL��
public:
	State(string _name, StageObject* _holder) :name_(_name), holder_(_holder) {}
	virtual void Initialize() = 0;  // ������
	virtual void Start() = 0;       // �J�n
	virtual void Update() = 0;      // �X�V
	string GetName() { return name_; }
};