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

	vector<UIObject*> objects_;

	UIButton* pUIButton_;
	UIImage* pUIImage_;

public:
	UIPanel();
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;

	void Save(json& _saveObj);
	void Load(json& _loadObj);
	void DrawData();

	void AddUIObject(UIObject* _object);
	void DeleteUIObject(UIObject* _object);
	void DeleteAllUIObject();

	//レイヤー番号順にソート
	void SortUIObject();

	///UIObject* GetUIObject(string _name);
	vector<UIObject*> GetUIObjects() { return objects_; };
};

