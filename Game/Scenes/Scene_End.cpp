#include "Scene_End.h"
#include "../Objects/UI/UIPanel.h"
#include "../../Engine/Global.h"
#include "../../Engine/ImGui/imgui.h"

Scene_End::Scene_End(GameObject* parent_)
{
}

void Scene_End::Initialize()
{
}

void Scene_End::Update()
{
	ImGui::Begin("result");
	ImGui::Text("time : %d",1234);
	ImGui::Text("score : %d", ScoreManager::GetScore());
	for (int i = 0; i < 13;i++)ImGui::NewLine();
	ImGui::Text("THANK YOU FOR PLAYING!");
	ImGui::End();
}

void Scene_End::Draw()
{
}

void Scene_End::Release()
{
}
