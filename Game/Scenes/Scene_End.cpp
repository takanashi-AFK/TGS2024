#include "Scene_End.h"
#include "../Objects/UI/UIPanel.h"

Scene_End::Scene_End(GameObject* parent_)
{
}

void Scene_End::Initialize()
{
	//// UIƒpƒlƒ‹‚Ì¶¬
	UIPanel* pUIPanel = Instantiate<UIPanel>(this); {
		json uiData;
		if (JsonReader::Load("Datas/UILayouts/EndScene.json", uiData))pUIPanel->Load(uiData);
	}
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
