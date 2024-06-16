#pragma once
#include "UIObject.h"

class UIButton : public UIObject
{
	string imageFilePath_;
public:
	UIButton(string _name, GameObject* parent);
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;

	void Save(json& saveObj) override;
	void Load(json& loadObj) override;
	void DrawData() override;
};

