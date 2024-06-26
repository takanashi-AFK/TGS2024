#pragma once

// インクルード
#include "../../../Engine/GameObject/GameObject.h"
#include "Components/Component.h"
#include <vector>

// using宣言
using std::vector;

/// <summary>
/// ステージに登場するオブジェクトのクラス
/// </summary>
class StageObject : public GameObject
{
protected:
	vector<Component*> myComponents_;   // 自身が保有するコンポーネント群
	string modelFilePath_;              // モデルのファイルパス
	int modelHandle_;                   // モデル番号
   
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="_name">オブジェクト名</param>
	/// <param name="_modelFilePath">モデルファイルパス</param>
	/// <param name="_parent">親オブジェクト</param>
	StageObject(string _name,string _modelFilePath,GameObject* _parent);

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
	/// 開放
	/// </summary>
	void Release() override;

	/// <summary>
	/// 保存
	/// </summary>
	/// <param name="_saveObj">保存データ</param>
	virtual void Save(json& _saveObj);

	/// <summary>
	/// 読込
	/// </summary>
	/// <param name="_loadObj">読込データ</param>
	virtual  void Load(json& _loadObj);

	/// <summary>
	/// ImGuiパネル表示
	/// </summary>
	virtual void DrawData();

	/// <summary>
	/// コンポーネントをリストに追加
	/// </summary>
	/// <param name="_comp">追加するコンポーネント</param>
	/// <returns>追加できたかどうか</returns>
	bool AddComponent(Component* _comp);

	/// <summary>
	/// コンポーネントをリストから削除
	/// </summary>
	/// <param name="_comp">削除するコンポーネント</param>
	/// <returns>削除できたかどうか</returns>
	bool DeleteComponent(Component* _comp);

	/// <summary>
	/// コンポーネントをリストから全て削除
	/// </summary>
	/// <returns>削除できたかどうか</returns>
	bool DeleteAllComponent();
};

/// <summary>
/// ステージオブジェクトを生成する関数
/// </summary>
/// <param name="_name"> オブジェクト名</param>
/// <param name="_modelFilePath"> モデルファイルパス</param>
/// <param name="_parent"> 親オブジェクト</param>
/// <returns>作成したオブジェクトのポインタ</returns>
StageObject* CreateStageObject(string _name, string _modelFilePath, GameObject* _parent);