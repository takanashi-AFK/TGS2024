#pragma once
#include "UIObject.h"

class Text;

struct FontData {
	string filePath;
	XMINT2 charSize;
	int rowLength;
};

class UIText : public UIObject
{
private:
	Text* pText_;	// テキストインスタンス
	string drawText_;	// 描画する文字列
	int* intNum_;		// 描画する数字
	
	float size_;		// テキストサイズ
	FontData fontData_;	// フォントデータ

	bool isOpenChangeFontWindow_;	// フォント変更ウィンドウを開くかどうか

public:
	/// <summary> コンストラクタ </summary>
	UIText(string _name, UIObject* parent, int _layerNum);

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
	/// <summary> 文字列を設定 </summary>
	void SetText(string _text) { drawText_ = _text; }
	
	/// <summary> 数字を設定 </summary>
	void SetText(int* _num) { intNum_ = _num; }

	/// <summary> テキストサイズを設定 </summary>
	void SetSize(float _size) { size_ = _size; }

/*
getter :*/
	/// <summary> 文字列を取得 </summary>
	string GetText() const { return drawText_; }

	/// <summary> 数字を取得 </summary>
	int* GetNum() const { return intNum_; }

	/// <summary> テキストサイズを取得 </summary>
	float GetSize() const { return size_; }

private:
	void ChangeFontWindow();

	bool GetFontFilePathFromExplorer(string& _filePath) const;
};

