#pragma once
#include "../../Otheres/UIObject.h"

class UIButton : public UIObject
{
private:

	//UIの画像
	int UIButtonPict_;
	//ボタンが押されたかどうか
	bool isButtonPushed_;
	//画像のサイズ
	XMFLOAT3 size_;
	//マウスの位置
	XMFLOAT3 mouseCenter_;

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="_name">UIオブジェクトの名前</param>
	/// <param name="_parent">親のオブジェクト</param>
	UIButton(string _name, GameObject* _parent);

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
	/// <param name="_saveUIobj"></param>
	void Save(json& _saveUIobj) override;

	/// <summary>
	/// 読み込み
	/// </summary>
	/// <param name="_loadUIobj"></param>
	void Load(json& _loadUIobj) override;

	//Imgui上でイージング関数の仕組みを確認するもの

	/// <summary>
	/// GUI上で表示
	/// </summary>
	void DrawGUI();

	/// <summary>
	/// 画像を設定
	/// </summary>
	void SetImage();

	/// <summary>
	/// マウスボタンの中に入っているか
	/// </summary>
	/// <param name="mousePos">マウスの現在地</param>
	/// <returns></returns>
	bool MouseInArea(XMFLOAT3 mousePos);

	/// <summary>
	/// 押されたか
	/// </summary>
	/// <param name="pushed">ボタンが押されたら</param>
	void ClickButton(bool pushed);
};

