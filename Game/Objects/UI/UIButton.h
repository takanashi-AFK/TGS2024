#pragma once
#include "../UI/UIObject.h"

class UIButton : public UIObject
{
private:

	int UIButtonPict_;
	XMFLOAT3 size_;//画像の大きさ

	struct Rect {
		float left;
		float top;
		float right;
		float bottom;
	};

public:
	/// <summary>
		/// コンストラクタ
		/// </summary>
		/// <param name="_parent"></param>
	UIButton(GameObject* _parent);

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
	/// <param name="_saveUIobj">保存したいボタンの情報</param>
	void Save(json& _saveUIobj) override;

	/// <summary>
	/// 読込
	/// </summary>
	/// <param name="_loadUIobj">読込したいボタンの情報</param>
	void Load(json& _loadUIobj) override;

	//Imgui上でいーじんぐ関数の仕組み見るためのやつ
	void DrawGui();

	//マウスがボタンの中に入ってるかどうか
	bool MouseInArea(XMFLOAT3 mousePos);

	//押されたかどうか
	bool ClickButton();

	//画像の座標敬に変換
	void ConvertToImageCoordinates(XMFLOAT3& _position);

};

