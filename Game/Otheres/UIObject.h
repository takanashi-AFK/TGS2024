#pragma once
#include"../../Engine/Json/JsonReader.h"
#include"../../Engine/GameObject/GameObject.h"
class UIObject: public GameObject
{

public:
	/// <summary>
	///コンストラクタ 
	/// </summary>
	/// <param name="_name">Uiのオブジェクトの名前</param>
	/// <param name="_parent">親オブジェクト</param>
	UIObject(std::string _name, GameObject* _parent);

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
   virtual void Save(json& _saveUiobj) = 0;

	 /// <summary>
    /// 読込
   /// </summary>
  /// <param name="_loadUiobj">読込データ</param>
  virtual void Load(json& _loadUiobj) = 0;
};

