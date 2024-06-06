#include "UIPanel.h"

#include "../../Objects/UI/UIButton.h"

UIPanel::UIPanel(GameObject* _parent)
	: UIObject("UIPanel", _parent)
{
}

UIPanel::~UIPanel()
{
}

void UIPanel::Initialize()
{
	//UIButtonクラスのインスタンスを生成
	UIButton * button = new UIButton(this);

	button->Initialize();
	AddChild(button);
}

void UIPanel::Update()
{
	//子オブジェクトを更新
	for (UIObject* child : childList) {
		child->Update();
	}

	//UIObject::Update();
}

void UIPanel::Draw()
{
	//子オブジェクトを描画
	for (UIObject* child : childList) {
		child->Draw();
	}
	//UIObject::Draw();
}

void UIPanel::Release()
{
	// 子オブジェクトをすべて削除
	ClearChildren();
}

void UIPanel::Save(json& _saveUiobj)
{
}
	
void UIPanel::Load(json& _loadUiobj)
{
}

void UIPanel::AddChild(UIObject* _child)
{
	// 子オブジェクトを追加
	childList.push_back(_child);
}

void UIPanel::RemoveChild(UIObject* _child)
{
	// 子オブジェクトを削除
	childList.remove(_child);
}

void UIPanel::ClearChildren()
{
	// childListの中身を参照してループ処理
	for (UIObject* child : childList) {
		// 子オブジェクトを解放
		child->Release();
		delete child;
	}
	// childListの中身を全て削除
	childList.clear();
}