#include "OptionMenu.h"

namespace OptionMenu
{
	bool isOptionMenu = false;
}


void OptionMenu::Draw()
{
	{
		ImGui::Begin("Options", &isOptionMenu, ImGuiWindowFlags_AlwaysAutoResize);

		// ���̑��̃I�v�V��������...

		// ����{�^��
		if (ImGui::Button("Close")) {
			isOptionMenu = false;
		}

		ImGui::End();

	}
}
