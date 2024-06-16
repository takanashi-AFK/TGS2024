#include "UIObject.h"

UIObject::UIObject(string _name, UIType _type, GameObject* parent)
	: GameObject(parent, _name), isEnable_(true), type_(_type)
{
}

UIObject* CreateUIObject(string _name, UIType _type, GameObject* _parent)
{
	// インスタンスを生成する
	UIObject* obj = nullptr;
	switch (_type)
	{
	case UI_BUTTON:break;
	case UI_IMAGE:break;
	case UI_TEXT:break;
	default:obj = new UIObject(_name, _type, _parent);break;
	}

	// インスタンスが生成できなかった場合はnullptrを返す
	if (obj == nullptr)return nullptr;

	// 親オブジェクトの子オブジェクトとして登録する
	if (_parent != nullptr)_parent->PushBackChild(obj);
	
	// 初期化を行う
	obj->Initialize();

	// 生成したオブジェクトを返す
	return obj;
}

string GetUITypeString(UIType _type)
{
	switch (_type)
	{
	case UI_BUTTON:return "BUTTON";
	case UI_IMAGE:return "IMAGE";
	case UI_TEXT:return "TEXT";
	default:return "UNKNOWN";
	}
}
