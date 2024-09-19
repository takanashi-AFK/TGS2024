#include "OptionMenu.h"
#include "../../Game/Objects/Camera/TPSCamera.h"
#include "../../Engine/GameObject/GameObject.h"

namespace OptionMenu
{
	bool isOptionMenu = false;
}


void OptionMenu::Draw(GameObject* pRootObject_)
{
	{
		ImGui::Begin("Options", &isOptionMenu, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);

		// •Â‚¶‚éƒ{ƒ^ƒ“
		if (ImGui::Button("Close Option")) {
			isOptionMenu = false;
		}
		TPSCamera* camera = (TPSCamera*)pRootObject_->FindObject("TPSCamera");
		if (pRootObject_ == nullptr)return;
		static float sens = 0;
		ImGui::DragFloat("SetSens",&sens,1,0,100);
		ImGui::SameLine();
		if(ImGui::Button("Sensitivity Confirm"))camera->SetSensitivity(sens);

		ImGui::End();

	}
}
