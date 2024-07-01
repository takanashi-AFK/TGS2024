#include "UIObject.h"

#include "../../../Engine/Global.h"
#include "../../../Engine/ImGui/imgui.h"

#include "UIPanel.h"
#include "UIButton.h"
#include "UIImage.h"
#include "UIText.h"
#include "UIProgressBar.h"

UIObject::UIObject(string _name, UIType _type, GameObject* parent)
	: GameObject(parent, _name), isEnable_(true), type_(_type), isPositionLocked_(false), isRotateLocked_(false), isScaleLocked_(false)
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

void UIObject::ChildDrawData()
{
	// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	// オブジェクト名を表示
	// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	ImGui::Text(this->objectName_.c_str());
	ImGui::SameLine();

	// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	// オブジェクトの削除ボタン
	// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	if (ImGui::SmallButton("delete"))((UIPanel*)FindObject("UIPanel"))->DeleteUIObject(this);
	ImGui::Separator();

	// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	// オブジェクトの名前を変更
	// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	if (ImGui::TreeNode("name")) {
		ImGui::Text("Current name : %s", this->objectName_.c_str());
		char buffer[256] = "";
		if (ImGui::InputTextWithHint("##Input", "Input New name...", buffer, IM_ARRAYSIZE(buffer)))
			this->objectName_ = buffer;
		ImGui::TreePop();
	}

	// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	// 自身の変形情報を描画
	// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	if (ImGui::TreeNode("transform_")) {
		if(isPositionLocked_ == false)ImGui::DragFloat3("position_", &transform_.position_.x, 0.1f);
		if(isRotateLocked_ == false)ImGui::DragFloat3("rotate_", &transform_.rotate_.x, 1.f, -360.f, 360.f);
		if(isScaleLocked_ == false)ImGui::DragFloat3("scale_", &transform_.scale_.x, 0.1f, 0.f, LONG_MAX);
		ImGui::TreePop();
}

	// 固有情報を描画
	this->DrawData();
}

UIObject* CreateUIObject(string _name, UIType _type, GameObject* _parent)
{
	// インスタンスを生成する
	UIObject* obj = nullptr;
	switch (_type)
	{
		case UI_BUTTON:obj = new UIButton(_name, _parent); break;
		case UI_IMAGE:obj = new UIImage(_name, _parent); break;
		case UI_TEXT: obj = new UIText(_name, _parent); break;
		case UI_PROGRESSBAR: obj = new UIProgressBar(_name, _parent); break;
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
	case UI_PROGRESSBAR:return "PROGRESSBAR";
	default:return "UNKNOWN";
	}
}
