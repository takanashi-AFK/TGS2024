#include "UIPanel.h"

// インクルード
#include "UIObject.h"

UIPanel::UIPanel(GameObject* parent)
	: GameObject(parent, "UIPanel"), objects_()
{
}

void UIPanel::Initialize()
{
}

void UIPanel::Update()
{
}

void UIPanel::Draw()
{
}

void UIPanel::Release()
{
}

void UIPanel::Save(json& _saveObj)
{
	// 各オブジェクトの保存処理
	for (auto obj : objects_)obj->ChildSave(_saveObj[obj->GetObjectName()]);
}

void UIPanel::Load(json& _loadObj)
{
	// 全てのオブジェクトを削除
	DeleteAllUIObject();

	for (auto it = _loadObj.begin(); it != _loadObj.end(); ++it) {

		// オブジェクトのインスタンスを生成
		UIObject* obj = CreateUIObject(it.key(), it.value()["type_"], this);

		// オブジェクト情報を読込
		obj->ChildLoad(it.value());

		// オブジェクトをリストに追加
		AddUIObject(obj);
	}
}

void UIPanel::DrawData()
{
	// 各オブジェクトの描画処理
	for (auto obj : objects_)obj->DrawData();
}

void UIPanel::AddUIObject(UIObject* _object)
{
	// リストに追加
	if (_object != nullptr)objects_.push_back(_object);
}

void UIPanel::DeleteUIObject(UIObject* _object)
{
	// オブジェクトを削除する
	_object->KillMe();

	// オブジェクトのイテレータを取得する
	auto it = std::find(objects_.begin(), objects_.end(), _object);

	// イテレータが見つかった場合、ベクターから削除する
	if (it != objects_.end()) objects_.erase(it);
}

void UIPanel::DeleteAllUIObject()
{
	// 全てのオブジェクトを削除
	for (auto obj : objects_)obj->KillMe();
	objects_.clear();
}

UIObject* UIPanel::GetUIObject(string _name)
{
	UIObject* result = nullptr;

	for (auto obj : objects_) {
		if (obj->GetObjectName() == _name) {
			result = obj;
			break;
		}
	}
	return result;
}
