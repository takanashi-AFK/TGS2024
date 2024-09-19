#pragma once
#include "UIObject.h"

class UIDragBar : public UIObject
{
	string barImageFilePath_;
	int barImageHandle_;

	Transform cursorTransform_;
	string cursorImageFilePath_;
	int cursorImageHandle_;

	int value_;
	float sliderValue;

public:
	UIDragBar(string _name, UIObject* parent, int _layerNum);
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;

	void Save(json& saveObj) override;
	void Load(json& loadObj) override;
	void DrawData() override;
	void SetImage(string _barImageFilePath, string _cursorImageFilePath);

	void SetValue(int& _value) { _value = value_; }

	void ConvertToImageCoordinates(XMFLOAT2& _position);
	bool IsMouseOver(XMFLOAT2 _mousePosition);

};

