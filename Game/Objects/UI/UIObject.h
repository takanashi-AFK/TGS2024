#pragma once
#include "../../../Engine/GameObject/GameObject.h"
#include <vector>
#include "../../../Engine/Json/JsonReader.h"

using std::vector;

enum UIType {
	UI_NONE,
	UI_BUTTON,
	UI_IMAGE,
	UI_TEXT,
	UI_MAX,
};

class UIObject : public GameObject
{
protected:
	bool isEnable_;	// —LŒø‚©‚Ç‚¤‚©
	UIType type_;	// UI‚ÌŽí—Þ
public:
	UIObject(string _name,UIType _type,GameObject* parent);

	virtual void Initialize() override{}
	virtual void Update() override{}
	virtual void Draw() override{}
	virtual void Release() override{}
	
	virtual void Save(json& saveObj) {};
	virtual void Load(json& loadObj) {};
	virtual void DrawData() {};

	void ChildSave(json& _saveObj);
	void ChildLoad(json& _loadObj);
	void ChildDrawData();
};

UIObject* CreateUIObject(string _name, UIType _type, GameObject* _parent);

string GetUITypeString(UIType _type);