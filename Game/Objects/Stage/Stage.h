#pragma once

// インクルード
#include "../../../Engine/GameObject/GameObject.h"
#include "../../../Engine/Json/JsonReader.h"
#include <vector>

// using宣言
using std::vector;

// 前方宣言
class StageObject;
class Component;

/// <summary>
/// ステージを管理するクラス
/// </summary>
class Stage : public GameObject
{
private:
	friend class GameEditor;		// StageEditorクラスをフレンド宣言
	vector<StageObject*> objects_;	// 自身が保有するステージオブジェクト群

public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="_parent">親オブジェクト</param>
	Stage(GameObject* _parent);

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
	/// <param name="_saveObj">保存データ</param>
	void Save(json& _saveObj);

	/// <summary>
	/// 読込
	/// </summary>
	/// <param name="_loadObj">読込データ</param>
	void Load(json& _loadObj);

	/// <summary>
	/// ImGuiパネル表示
	/// </summary>
	void DrawData();

	/// <summary>
	/// オブジェクトをリストに追加
	/// </summary>
	/// <param name="_obj">追加するオブジェクト</param>
	void AddStageObject(StageObject* _obj);

	/// <summary>
	/// オブジェクトをリストから削除
	/// </summary>
	/// <param name="_obj">削除するオブジェクト</param>
	void DeleteStageObject(StageObject* _obj);

	/// <summary>
	/// リスト内のオブジェクトを全て削除
	/// </summary>
	void DeleteAllStageObject();

	/// <returns>
	/// オブジェクトリストを取得
	/// </returns>
	vector<StageObject*>& GetStageObjects() { return objects_; }

	Component* FindComponent(string _name);
};

