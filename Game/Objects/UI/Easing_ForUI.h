#pragma once
#include "UIObject.h"
#include "../../../Engine/DirectX/Easing.h"

class Easing_ForUI
{
public:
	Easing_ForUI(UIObject* p);
	~Easing_ForUI();

	void Save(json& _saveObj);
	void Load(json& _loadObj);

	Transform GetValue();
	Easing* GetEasing();

	Transform secTransform_;

private:
	Easing easing_;

	UIObject* p_ui;
};

