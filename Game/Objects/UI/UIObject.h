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
private:
	bool isPositionLocked_;
	bool isRotateLocked_;
	bool isScaleLocked_;

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

	void LockPosition() { isPositionLocked_ = true; }
	void LockRotate() { isRotateLocked_ = true; }
	void LockScale() { isScaleLocked_ = true; }

	void UnlockPosition() { isPositionLocked_ = false; }
	void UnlockRotate() { isRotateLocked_ = false; }
	void UnlockScale() { isScaleLocked_ = false; }
};

UIObject* CreateUIObject(string _name, UIType _type, GameObject* _parent);
string GetUITypeString(UIType _type);