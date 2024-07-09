#pragma once
#include "../../../Engine/Json/JsonReader.h"
#include <vector>
#include "UIObject.h"

class UIButton;
class UIImage;
class UIPanel;

extern UIPanel* pUIPanel_;
using std::vector;


class UIPanel : public UIObject
{
private:

	UIButton* pUIButton_;
	UIImage* pUIImage_;

public:
	UIPanel();
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;

	void Save(json& _saveObj)override;
	void Load(json& _loadObj)override;
	void DrawData()override;

	//void AddUIObject(UIObject* _object);
	void DeleteUIObject(UIObject* _object);
	void DeleteAllUIObject();

	//レイヤー番号順にソート
	void SortUIObject();
	vector<UIObject*> GetUIObjects() { return childList_; };

};

