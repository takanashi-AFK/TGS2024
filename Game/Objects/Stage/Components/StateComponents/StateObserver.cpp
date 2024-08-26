#include "StateObserver.h"
#include "../StateComponents/Component_StateManager.h"
#include "../../../Stage/StageObject.h"


bool StateObserver::Entry(StageObject* _holder)
{
    // �ۗL�҂����A��ԊǗ��R���|�[�l���g���擾
    vector<Component*> comps = _holder->FindComponent(ComponentType::StateManager);

    bool isEntry = false;
    // ��ԊǗ��R���|�[�l���g�����݂���ꍇ�A�I�u�U�[�o�[���X�g�ɓo�^
    for (auto comp_stateManager : comps) {
        if (comp_stateManager != nullptr) ((Component_StateManager*)comp_stateManager)->AddObserver(this);
        isEntry = true;
    }

    return isEntry;
}
