#pragma once

// インクルード
#include "../../../Engine/GameObject/GameObject.h"
#include "../../../Engine/Json/JsonReader.h"
#include <vector>

// using宣言
using std::vector;

// 前方宣言
class StageObject;

// ステージを管理するクラス
class Stage : public GameObject
{
	friend class StageEditor;

private:
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
	/// <param name="_saveObj"></param>
	void Save(json& _saveObj);

	/// <summary>
	/// 読込
	/// </summary>
	/// <param name="_saveObj"></param>
	void Load(json& _loadObj);

	/// <summary>
	/// ImGui描画
	/// </summary>
	void DrawData();

	/// <summary>
	/// オブジェクトをリストに追加
	/// </summary>
	/// <param name="_obj">追加するオブジェクトのアドレス</param>
	void AddStageObject(StageObject* _obj);

	/// <summary>
	/// オブジェクトをリストから削除
	/// </summary>
	/// <param name="_obj">削除するオブジェクトのアドレス</param>
	void DeleteStageObject(StageObject* _obj);

	/// <summary>
	/// リスト内のオブジェクトをすべて削除
	/// </summary>
	void DeleteAllStageObject();
};

