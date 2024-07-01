#pragma once
#include <vector>
#include "../../../Engine/Json/JsonReader.h"
#include "../../../../../Engine/GameObject/Transform.h"
#include "../../../../../Engine/Collider/BoxCollider.h"
#include "../../../../../Engine/Collider/SphereCollider.h"


using std::vector;

enum UIType {
	UI_NONE,
	UI_BUTTON,
	UI_IMAGE,
	UI_TEXT,
	UI_MAX,
};

class UIObject
{
protected:
	std::string objectName_; // オブジェクト名
	Transform transform_; // 位置や向きなどを管理するオブジェクト
	bool isEnable_;	// 有効かどうか
	UIType type_;	// UIの種類
	int layerNumber_; // レイヤー番号
	std::vector<UIObject*> childList_;  // 子オブジェクトのリスト


	
	

	// 親オブジェクト
	UIObject* pParent_;

	//フラグ
	struct UI_STATE
	{
		unsigned initialized : 1;	//初期化済みか
		unsigned entered : 1;		//更新するか
		unsigned visible : 1;		//描画するか
		unsigned dead : 1;			//削除するか
	};
	UI_STATE state_;

public:

	//コンストラクタ
	UIObject(string _name,UIType _type,UIObject* parent, int _layerNum);
   
	//デストラクタ
	virtual ~UIObject();

	//各オブジェクトで必ず作る関数
	virtual void Initialize(void) = 0;
	virtual void Update(void) = 0;
	virtual void Draw() = 0;
	virtual void Release(void) = 0;

	//自分の該当関数を読んだ後、子供の関数も呼ぶ
	void UpdateSub();
	void DrawSub();
	void ReleaseSub();

	bool IsDead(); //削除するかどうか


	virtual void Save(json& saveObj) {};
	virtual void Load(json& loadObj) {};
	virtual void DrawData() {};
	  
	void ChildSave(json& _saveObj);
	void ChildLoad(json& _loadObj);
	void ChildDrawData();

	void KillMe();			// 自分を削除する

	//名前でオブジェクトを検索（対象は自分の子供以下）
	//引数：name	検索する名前
	//戻値：見つけたオブジェクトのアドレス（見つからなければnullptr）
	UIObject* FindChildObject(const std::string& name);


	UIObject* FindObject(const std::string& name){ return GetRootJob()->FindChildObject(name); }


	//オブジェクトの名前を取得
	//戻値：名前
	const std::string& GetObjectName(void) const;

	//Rootオブジェクトを取得(UIPanel)
	UIObject* GetRootJob();

	//親オブジェクトを取得
	UIObject* GetParent();

	/// <summary>
	/// 子オブジェクトを追加(リストの最後へ)
	/// </summary>
	/// <param name="obj"></param>
	void PushBackChild(UIObject* obj);

	// Getter
	int GetLayerNumber() { return layerNumber_; }

	//オブジェクトをレイヤー番号で比較するための関数
	static bool CompareLayerNumber(UIObject* _object1, UIObject* _object2);

	//子オブジェクトをソートするための関数
	void SortChildren();

};

UIObject* CreateUIObject(string _name, UIType _type, UIObject* _parent, int _layerNum);
string GetUITypeString(UIType _type);


//オブジェクトを作成するテンプレート
template <class T>
T* Instantiate(UIObject* pParent)
{
	T* pNewObject = new T(pParent);
	if (pParent != nullptr)
	{
		pParent->PushBackChild(pNewObject);
	}
	pNewObject->Initialize();
	return pNewObject;
}

