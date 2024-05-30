#pragma once
#include "../../Otheres/UIObject.h"

class UIButton : public UIObject
{
private:

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="_name">UIオブジェクトの名前</param>
	/// <param name="_modelFilePath">モデルファイルパス</param>
	/// <param name="_parent">親オブジェクト</param>
	UIButton(string _name, string _modelFilePath, GameObject* _parent);

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
	/// <param name="_saveUiobj"></param>
	void Save(json& _saveUiobj) override;

	/// <summary>
	/// 読み込み
	/// </summary>
	/// <param name="_loadUiobj"></param>
	void Load(json& _loadUiobj) override;


};

