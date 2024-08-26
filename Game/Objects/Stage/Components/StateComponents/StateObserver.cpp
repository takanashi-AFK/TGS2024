#include "StateObserver.h"
#include "../StateComponents/Component_StateManager.h"
#include "../../../Stage/StageObject.h"


bool StateObserver::Entry(StageObject* _holder)
{
    // 保有者が持つ、状態管理コンポーネントを取得
    vector<Component*> comps = _holder->FindComponent(ComponentType::StateManager);

    bool isEntry = false;
    // 状態管理コンポーネントが存在する場合、オブザーバーリストに登録
    for (auto comp_stateManager : comps) {
        if (comp_stateManager != nullptr) ((Component_StateManager*)comp_stateManager)->AddObserver(this);
        isEntry = true;
    }

    return isEntry;
}
