#pragma once
#include "UIObject.h"
class UILayerNumber : public UIObject
{
private:

	int layerNumber_;

public:

	UILayerNumber(string _name, GameObject* parent, int _layerNum);
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;

	void Save(json& saveObj) override;
	void Load(json& loadObj) override;
	void DrawData() override;




};

