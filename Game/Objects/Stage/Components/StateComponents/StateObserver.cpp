#include "StateObserver.h"
#include "../StateComponents/Component_StateManager.h"
#include "../../../Stage/StageObject.h"


void StateObserver::Initialize(StageObject* holder_)
{
   // 状態管理コンポーネントを取得
   Component_StateManager* comp_stateManager = (Component_StateManager*)holder_->FindComponent("StateManagerComponent");

   // nullじゃなければ、オブザーバーとしてStateManagerに追加
   if (comp_stateManager != nullptr) comp_stateManager->AddStateObserver(this);
}
