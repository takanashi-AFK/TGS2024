#pragma once
#include "../../Otheres/UIObject.h"
#include <list>

class UIPanel : public UIObject
{
protected:

	std::list<UIObject*> childList;	//子オブジェクトリスト

private:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="_name">UIオブジェクトの名前</param>
	/// <param name="_parent">親のオブジェクト</param>
	UIPanel(string _name,GameObject* _parent);

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize() override;

	/// <summary>
	/// 更新
	/// </summary>
	void Update() override;

	/// <summary>
	/// 描画
	/// </summary>
	void Draw() override;

	/// <summary>
	/// 解放
	/// </summary>
	void Release() override;

	/// <summary>
	/// 保存
	/// </summary>
	/// <param name="_saveUiobj">保存データ</param>
	void Save(json& _saveUiobj) override;

	/// <summary>
	/// 読み込み
	/// </summary>
	/// <param name="_loadUiobj">読み込みデータ</param>
	void Load(json& _loadUiobj) override;

	/// <summary>
	/// パネルに子オブジェクトを追加
	/// </summary>
	/// <param name="_child">追加したい子オブジェクト</param>
	void AddChild(UIObject* _child);

	/// <summary>
	/// パネルから指定した子オブジェクトを削除
	/// </summary>
	/// <param name="_child">削除したい子オブジェクト</param>
	void RemoveChild(UIObject* _child);

	/// <summary>
	/// パネル内の子オブジェクトを全て削除
	/// </summary>
	void ClearChild();
};

