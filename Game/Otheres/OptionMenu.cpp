#include "OptionMenu.h"

namespace OptionMenu
{
	bool isOptionMenu = false;
}


void OptionMenu::Draw()
{
	{
		ImGui::Begin("Options", &isOptionMenu, ImGuiWindowFlags_AlwaysAutoResize);

		// その他のオプション項目...

		// 閉じるボタン
		if (ImGui::Button("Close")) {
			isOptionMenu = false;
		}

		ImGui::End();

	}
}
