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
	bool isEnable_;	// óLå¯Ç©Ç«Ç§Ç©
	UIType type_;	// UIÇÃéÌóﬁ
	int layerNumber_; // ÉåÉCÉÑÅ[î‘çÜ

public:
	UIObject(string _name,UIType _type,GameObject* parent, int _layerNum);
   
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

	// Getter
	int GetLayerNumber() { return layerNumber_; }
};

UIObject* CreateUIObject(string _name, UIType _type, GameObject* _parent, int _layerNum);
string GetUITypeString(UIType _type);