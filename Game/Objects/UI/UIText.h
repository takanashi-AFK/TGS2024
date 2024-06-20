#pragma once
#include "UIObject.h"

class Text;

class UIText : public UIObject
{
private:
	Text* pText_;
	string drawText_;
public:
	UIText(string _name, GameObject* parent);
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;

	void Save(json& saveObj) override;
	void Load(json& loadObj) override;
	void DrawData() override;

};

