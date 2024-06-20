#pragma once
#include "UIObject.h"

class Text;

class UIText : public UIObject
{
private:
	Text* pText_;
	string drawText_;
	float size_;

	float* floatNum_;

public:
	UIText(string _name, GameObject* parent);
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;

	void Save(json& saveObj) override;
	void Load(json& loadObj) override;
	void DrawData() override;

	void SetText(string _text) { drawText_ = _text; }
	void SetText(float* _num) { floatNum_ = _num; }
};

