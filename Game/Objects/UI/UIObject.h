#pragma once
#include "../../../Engine/GameObject/GameObject.h"
#include <vector>
#include "../../../Engine/Json/JsonReader.h"

using std::vector;

enum UIType {
	BUTTON,
	IMAGE,
	TEXT,
	MAX
};

class UIObject : public GameObject
{
protected:
	bool isEnable_;	// 有効かどうか
	UIType type_;	// UIの種類
public:
	UIObject(string _name,UIType _type,GameObject* parent);

	virtual void Initialize() override{}
	virtual void Update() override{}
	virtual void Draw() override{}
	virtual void Release() override{}
	
	virtual void Save(json& saveObj) {};
	virtual void Load(json& loadObj) {};
	virtual void DrawData() {};

};

UIObject* CreateUIObject(string _name, UIType _type, GameObject* _parent);

string GetUITypeString(UIType _type);