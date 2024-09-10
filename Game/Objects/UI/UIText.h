#pragma once
#include "UIObject.h"

class Text;

class UIText : public UIObject
{
private:
	Text* pText_;
	string drawText_;
	float size_;
	string fontFilePath_;

	int* intNum_;

	int charWidth;
	int charHeight;
	int rowLength;

	bool openChangeFontDialog_;

public:
	UIText(string _name, UIObject* parent, int _layerNum);
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;

	void Save(json& saveObj) override;
	void Load(json& loadObj) override;
	void DrawData() override;

	void SetText(string _text) { drawText_ = _text; }
	void SetText(int* _num) { intNum_ = _num; }

	void OpenChangeFontDialog();
};

