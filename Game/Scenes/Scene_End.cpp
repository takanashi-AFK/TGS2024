#include "Scene_End.h"
#include "../Objects/UI/UIPanel.h"

Scene_End::Scene_End(GameObject* parent_ /*,ENDSTATE state_*/)
{
}

void Scene_End::Initialize()
{
	////// UI�p�l���̐���
	//UIPanel* pUIPanel = Instantiate<UIPanel>(this);{
	//	json uiData;
	//	if (JsonReader::Load("Datas/UILayouts/EndScene.json", uiData))pUIPanel->Load(uiData);
	//}

    /*switch (endState_)
    {
    case WIN:
        JsonReader::Load("Datas/UILayouts/EndScene.json", uiData);
        pUIPanel->Load(uiData);
        break;
    case LOSE:
        JsonReader::Load("Datas/UILayouts/EndScene.json", uiData);
        pUIPanel->Load(uiData);
        break;
   
    }*/
    
}

void Scene_End::Update()
{
}

void Scene_End::Draw()
{
}

void Scene_End::Release()
{
}
