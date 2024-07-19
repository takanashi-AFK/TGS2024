#pragma once
#include "../../../Engine/Json/JsonReader.h"
#include <vector>
#include "UIObject.h"


using std::vector;


class UIPanel : public UIObject
{
private:

	//シングルトンインスタンス
	static UIPanel* instance_;

	//コンストラクタ
	UIPanel();

	// コピーコンストラクタの削除
	UIPanel(const UIPanel&) = delete;
	// 代入演算子の削除
	UIPanel& operator=(const UIPanel&) = delete;

public:

	

	//シングルトンインスタンスの取得
	static UIPanel* GetInstance();
	
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;

	void Save(json& _saveObj)override;
	void Load(json& _loadObj)override;
	void DrawData()override;

	void DeleteUIObject(UIObject* _object);
	void DeleteAllUIObject();

	//レイヤー番号順にソート
	void SortUIObject();
	vector<UIObject*> GetUIObjects() { return childList_; };
};

