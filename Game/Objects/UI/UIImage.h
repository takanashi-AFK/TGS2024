#pragma once
#include "UIObject.h"

class UIImage : public UIObject
{
private:
	string imageFilePath_;
	int imageHandle_;
	bool isDraw_;
public:
	UIImage(string _name, UIObject* parent, int _layerNum);
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;

	void Save(json& saveObj) override;
	void Load(json& loadObj) override;
	void DrawData() override;

	void SetImage(string _imageFilePath);
	void SetEnable(bool _enable) { isDraw_ = _enable; }
	bool GetEnable() { return isDraw_; }
};

