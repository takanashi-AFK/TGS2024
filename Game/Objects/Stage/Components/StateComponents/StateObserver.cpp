#include "StateObserver.h"
#include "../StateComponents/Component_StateManager.h"
#include "../../../Stage/StageObject.h"


void StateObserver::Initialize(StageObject* holder_)
{
   // ��ԊǗ��R���|�[�l���g���擾
   Component_StateManager* comp_stateManager = (Component_StateManager*)holder_->FindComponent("StateManagerComponent");

   // null����Ȃ���΁A�I�u�U�[�o�[�Ƃ���StateManager�ɒǉ�
   if (comp_stateManager != nullptr) comp_stateManager->AddStateObserver(this);
}
