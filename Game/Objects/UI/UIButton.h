#pragma once
#include "UIObject.h"

class UIButton : public UIObject
{
private:
	string imageFilePath_; // 画像ファイルパス
	int imageHandle_;		// 画像ハンドル
public:
	/// <summary> コンストラクタ </summary>
	UIButton(string _name, UIObject* parent, int _layerNum);
	
	/// <summary> 初期化 </summary>
	void Initialize() override;
	
	/// <summary> 更新 </summary>
	void Update() override;
	
	/// <summary> 描画 </summary>
	void Draw() override;
	
	/// <summary> 解放 </summary>
	void Release() override;

	/// <summary> 保存 </summary>
	void Save(json& saveObj) override;
	
	/// <summary> 読込 </summary>
	void Load(json& loadObj) override;
	
	/// <summary> ImGui表示 </summary>
	void DrawData() override;

/*
setter :*/
	/// <summary> 画像ファイルパスを設定 </summary>
	void SetImage(string _imageFilePath);

/*
predicate :*/
	/// <summary> ボタンがクリックされたか </summary>
	bool OnClick();

	/// <summary> マウスがボタンの上にあるか </summary>
	bool IsMouseOver(XMFLOAT2 _position);
private:
	/// <summary> 画像座標を画面座標に変換 </summary>
	void ConvertToImageCoordinates(XMFLOAT2& _position);
};

