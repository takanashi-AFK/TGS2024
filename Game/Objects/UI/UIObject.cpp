#include "UIObject.h"

#include "UIButton.h"
#include "../../../Engine/Global.h"

UIObject::UIObject(string _name, UIType _type, GameObject* parent)
	: GameObject(parent, _name), isEnable_(true), type_(_type)
{
}

void UIObject::ChildSave(json& _saveObj)
{
	// タイプを保存
	_saveObj["type_"] = type_;
	
	// オブジェクト名を保存
	_saveObj["objectName_"] = objectName_;

	// 自身の変形行列情報を保存
	_saveObj["position_"] = { REFERENCE_XMFLOAT3(transform_.position_) };
	_saveObj["rotate_"] = { REFERENCE_XMFLOAT3(transform_.rotate_) };
	_saveObj["scale_"] = { REFERENCE_XMFLOAT3(transform_.scale_) };

	// 自身の固有情報を保存
	this->Save(_saveObj);
}

void UIObject::ChildLoad(json& _loadObj)
{
	// タイプを読込
	if(_loadObj.contains("type_"))type_ = (UIType)_loadObj["type_"].get<int>();

	// オブジェクト名を読込
	if (_loadObj.contains("objectName_"))objectName_ = _loadObj["objectName_"];

	// 変形行列情報を読込
	if (_loadObj.contains("position_"))transform_.position_ = { _loadObj["position_"][0].get<float>(),_loadObj["position_"][1].get<float>(), _loadObj["position_"][2].get<float>() };
	if (_loadObj.contains("rotate_"))transform_.rotate_ = { _loadObj["rotate_"][0].get<float>(),_loadObj["rotate_"][1].get<float>(), _loadObj["rotate_"][2].get<float>() };
	if (_loadObj.contains("scale_"))transform_.scale_ = { _loadObj["scale_"][0].get<float>(),_loadObj["scale_"][1].get<float>(), _loadObj["scale_"][2].get<float>() };

	// 固有情報を読込
	this->Load(_loadObj);
}

UIObject* CreateUIObject(string _name, UIType _type, GameObject* _parent)
{
	// インスタンスを生成する
	UIObject* obj = nullptr;
	switch (_type)
	{
	case UI_BUTTON:obj = new UIButton(_name, _parent); break;
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
