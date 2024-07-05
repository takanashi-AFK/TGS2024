#include "UIButton.h"
#include "../../../Engine/Global.h"
#include "../../../Engine/ImGui/imgui.h"
#include "UIImage.h"
#include "UIPanel.h"

UIObject::UIObject():
	UIObject("",UI_NONE,nullptr,0)
{

}

UIObject::UIObject(UIObject* parent):
	UIObject("",UI_NONE,parent,0)
{
}

UIObject::UIObject(string _name, UIType _type, UIObject* parent, int _layerNum)
	:objectName_(_name), type_(_type), pParent_(parent), layerNumber_(_layerNum), isEnable_(true)
{

	childList_.clear();
	state_ = { 0, 1, 1, 0 };

	if (parent)
		transform_.pParent_ = &parent->transform_;

}

UIObject::~UIObject()
{
}

void UIObject::ChildSave(json& _saveObj)
{
	// タイプを保存
	_saveObj["type_"] = type_;
	
	// オブジェクト名を保存
	_saveObj["objectName_"] = objectName_;

	// レイヤー番号を保存
	_saveObj["layerNumber_"] = layerNumber_;

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

	// レイヤー番号を読込
	if (_loadObj.contains("layerNumber_"))layerNumber_ = _loadObj["layerNumber_"].get<int>();

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
	if (ImGui::SmallButton("delete"))((UIPanel*)GetParent())->DeleteUIObject(this);
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
		ImGui::DragFloat3("position_", &transform_.position_.x, 0.1f);
		ImGui::DragFloat3("rotate_", &transform_.rotate_.x, 1.f, -360.f, 360.f);
		ImGui::DragFloat3("scale_", &transform_.scale_.x, 0.1f, 0.f, LONG_MAX);
		ImGui::TreePop();
	}


	// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	// レイヤー番号を描画
	// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	if (ImGui::TreeNode("LayerNumber"))
	{
		ImGui::Text("Image Layer Number: %d", GetLayerNumber());
		ImGui::InputInt("Layer Number", &layerNumber_);
		//layerNumbertが0以下場合は1にする
		if (layerNumber_ <= 0)layerNumber_ = 1;

		ImGui::TreePop();
	}
	// 固有情報を描画
	this->DrawData();
}

void UIObject::KillMe()
{
	state_.dead = 1;
}

UIObject* UIObject::FindChildObject(const std::string& name)
{
	//子供がいないなら終わり
	if (childList_.empty())
		return nullptr;

	//イテレータ
	auto it = childList_.begin();	//先頭
	auto end = childList_.end();	//末尾

	//子オブジェクトを1個ずつ探す
	while (it != end)
	{
		//同じ名前のオブジェクトを見つけたらそれを返す
		if((*it)->GetObjectName() == name)
			return *it;

		//その子供（孫）以降にいないか探す
		UIObject* obj = (*it)->FindChildObject(name);
		if (obj != nullptr) {
			return obj;
		}

		//次の子へ
		it++;
	}

	//見つからなかった
	return nullptr;
}

const std::string& UIObject::GetObjectName(void) const
{
	return objectName_;
}

UIObject* UIObject::GetRootJob()
{
	if (GetParent() == nullptr)
	{
		return this;
	}
	else return GetParent()->GetRootJob();
}

UIObject* UIObject::GetParent(void)
{
	return pParent_;
}

void UIObject::PushBackChild(UIObject* obj)
{
	assert(obj != nullptr);

	obj->pParent_ = this;
	childList_.push_back(obj);

}

bool UIObject::CompareLayerNumber(UIObject* _object1, UIObject* _object2)
{
	return _object1->GetLayerNumber() < _object2->GetLayerNumber();
}


//void UIObject::AddUIObject(UIObject* _object)
//{
//	// リストに追加
//	if (_object != nullptr)childList_.push_back(_object);
//}
//
//void UIObject::DeleteUIObject(UIObject* _object)
//{
//	// オブジェクトを削除する
//	_object->KillMe();
//
//	// オブジェクトのイテレータを取得する
//	auto it = std::find(childList_.begin(), childList_.end(), _object);
//
//	// イテレータが見つかった場合、ベクターから削除する
//	if (it != childList_.end()) childList_.erase(it);
//}
//
//void UIObject::DeleteAllUIObject()
//{
//	// 全てのオブジェクトを削除
//	for (auto obj : childList_)obj->KillMe();
//	childList_.clear();
//}


UIObject* CreateUIObject(string _name, UIType _type,UIObject* _parent, int _layerNum)
{
	// インスタンスを生成する
	UIObject* obj = nullptr;
	switch (_type)
	{
		case UI_BUTTON:obj = new UIButton(_name, _parent,_layerNum); break;
		case UI_IMAGE:obj = new UIImage(_name, _parent,_layerNum); break;
		case UI_TEXT:break;
		case UI_PANEL:obj = new UIPanel(); break;
        default:obj = nullptr; break;
		//default:obj = new UIObject(_name, _type, _parent, _layerNum); break;
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

void UIObject::UpdateSub()
{
	Update();
	Transform();

	for (auto it = childList_.begin(); it != childList_.end(); it++)
	{
		(*it)->UpdateSub();
	}
}

void UIObject::DrawSub()
{
	Draw();

	for (auto it = childList_.begin(); it != childList_.end(); it++)
	{
		(*it)->DrawSub();
	}

}

void UIObject::ReleaseSub()
{
	

	for (auto it = childList_.begin(); it != childList_.end();)
	{
		(*it)->ReleaseSub();
		SAFE_DELETE(*it);
		it = childList_.erase(it);
	}

	Release();
}

bool UIObject::IsDead()
{
	return (state_.dead != 0);
}
