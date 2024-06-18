#pragma once
#include "../../../Engine/GameObject/GameObject.h"
#include "../../../Engine/Json/JsonReader.h"
#include <vector>

class UIObject;

using std::vector;

class UIPanel : public GameObject
{
private:
	vector<UIObject*> objects_;

public:
	UIPanel(GameObject* parent);
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

	UIObject* GetUIObject(string _name);
	vector<UIObject*> GetUIObjects() { return objects_; };
};

