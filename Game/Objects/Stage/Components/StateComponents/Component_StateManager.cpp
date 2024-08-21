#include "Component_StateManager.h"
#include "../../StageObject.h"
void Component_StateManager::Initialize()
{
    // �e��Ԃ̏��������s��
    for (auto state : stateList_)state.second->Initialize();
}

void Component_StateManager::Update()
{
    // ��Ԃ̕ύX���� //////
    {
        // ��Ԃ��J�ډ\�ȏꍇ�J�ڂ���
        if (count_ >= changeLimit_) {
            currentStateKey_ = changeStateKey_;  // �ύX
            stateList_[currentStateKey_]->Start();
        }
        count_ += 1 / FPS;  // �J�E���g��i�߂�
    }

    // �L�[�Ŏw�肳�ꂽ��Ԃ����݂��邩�ǂ������m�F���A���݂̏�Ԃ̍X�V���������s
    if (stateList_.find(currentStateKey_) != stateList_.end()) stateList_[currentStateKey_]->Update();

}

void Component_StateManager::DrawData()
{
    // ��Ԓǉ��p�E�B���h�E
    if (g_isAddStateWindowOpen)DrawAddStateWindow(this);

    // �ǉ�����Ă����Ԃ��c���[�m�[�h�ŕ\��
    if (ImGui::TreeNode("State list")) {

        ImGui::SameLine();
        // ��Ԃ�ǉ�
        if (ImGui::SmallButton("Add State"))g_isAddStateWindowOpen = true;

        ImGui::TreePop();
    }
}


// ��Ԃ�ǉ�����ۂɕ\������ImGui�E�B���h�E�\���p�֐�
void Component_StateManager::DrawAddStateWindow(Component_StateManager * _stateManager)
{
    // ���O��ݒ�
    static char inputText[256] = {}; // �o�b�t�@���`
    ImGui::InputText("Enter Here State Name", inputText, sizeof(inputText));

    // ���f���̃t�@�C���p�X���擾���ݒ�
	string modelFilePath = holder_->GetModelFilePath();
    // ���f���̃A�j���[�V�������i���x/�ő�t���[��/�J�n�t���[���j��ݒ�
    float animSpeed = /*..�擾..*/; 
    float animMaxFrame = /*..�擾..*/;
    float animStartFrame = /*..�擾..*/;

    // ��L�̏�����ɏ�ԃC���X�^���X���쐬
    State* state = new State(inputText, holder_);
    state->SetModel(modelFilePath, animSpeed, animMaxFrame, animStartFrame);

    // ��Ԃ�ǉ�
    _stateManager->AddState(state);
    g_isAddStateWindowOpen = false;
}