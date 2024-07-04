#include "UIPanel.h"
#include "UIButton.h"
#include "UIImage.h"
#include "../../Otheres/GameEditor.h"

UIPanel* pUIPanel_ = new UIPanel;

UIPanel::UIPanel()
	: UIObject("UIPanel",UI_PANEL,nullptr,0)
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
	//レイヤー番号でオブジェクトをソート
	SortUIObject();
	// 各オブジェクトの描画処理
	for (auto obj : childList_)
	{
		//obj->SortChildren();
		obj->DrawData();

	}

	//SortChildren();

	/*SortUIObject();
	DrawData();*/

}

void UIPanel::Release()
{
	DeleteAllUIObject();
}

void UIPanel::Save(json& _saveObj)
{
	// 各オブジェクトの保存処理
	for (auto obj : childList_)obj->ChildSave(_saveObj[obj->GetObjectName()]);
}

void UIPanel::Load(json& _loadObj)
{
	// 全てのオブジェクトを削除
	DeleteAllUIObject();

	for (auto it = _loadObj.begin(); it != _loadObj.end(); ++it) {

		// レイヤー番号を読み取る
		int layerNumber = it.value().value("layerNumber", 0);  // デフォルト値0

		// オブジェクトのインスタンスを生成
		UIObject* obj = CreateUIObject(it.key(), it.value()["type_"], this,layerNumber);

		// オブジェクト情報を読込
		obj->ChildLoad(it.value());

		// オブジェクトをリストに追加
		//AddUIObject(obj);
	}
}

void UIPanel::DrawData()
{
	// 各オブジェクトのツリーの描画
	for (auto obj : childList_)
	{
		obj->DrawData();
	}
}

//void UIPanel::AddUIObject(UIObject* _object)
//{
//	// リストに追加
//	if (_object != nullptr)childList_.push_back(_object);
//}

void UIPanel::DeleteUIObject(UIObject* _object)
{
	// オブジェクトを削除する
	_object->KillMe();

	// オブジェクトのイテレータを取得する
	auto it = std::find(childList_.begin(), childList_.end(), _object);
	// イテレータが見つかった場合、ベクターから削除する
	if (it != childList_.end()) childList_.erase(it);

	////chaildList_にある子オブジェクトのReleaseを呼ぶ
	//for (auto obj : childList_) {
	//	obj->Release();
	//}



}

void UIPanel::DeleteAllUIObject()
{
	// 全てのオブジェクトを削除
	for (auto obj : childList_)obj->KillMe();
	childList_.clear();
}


void UIPanel::SortUIObject()
{
	// レイヤー番号でソート
	std::sort(childList_.begin(), childList_.end(), UIObject::CompareLayerNumber);
}


//UIObject* UIPanel::GetUIObject(string _name)
//{
//	UIObject* result = nullptr;
//
//	for (auto obj : childList_) {
//		if (obj->GetObjectName() == _name) {
//			result = obj;
//			break;
//		}
//	}
//	return result;
//}
