#pragma once

// インクルード
#include "Engine/GameObject/GameObject.h"
#include "Component.h"
#include <vector>

// using宣言
using std::vector;

// ステージに登場するオブジェクトのクラス
class StageObject:public GameObject
{
private:
    vector<Component*> myComponents_;   // 自身が保有するコンポーネント群
    string modelFilePath_;              // モデルのファイルパス
    int modelHandle_;                   // モデル番号
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    StageObject(string _name,string _modelFilePath,GameObject* _parent);

    /// <summary>
    /// 使用するコンポーネントを追加
    /// </summary>
    /// <param name="_comp">使用するコンポーネントのアドレス</param>
    /// <returns>成功失敗判定</returns>
    bool AddComponent(Component* _comp);

    /// <summary>
    /// 追加されたコンポーネントを削除
    /// </summary>
    /// <param name="_comp">削除するコンポーネントのアドレス</param>
    /// <returns></returns>
    bool DeleteComponent(Component* _comp);

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
};

/// <summary>
/// ステージオブジェクトを生成する関数
/// </summary>
/// <param name="_name"> オブジェクト名</param>
/// <param name="_modelFilePath"> モデルのファイルパス</param>
/// <param name="_parent"> 親オブジェクト</param>
/// <returns>オブジェクトのアドレス</returns>
StageObject* CreateStageObject(string _name, string _modelFilePath, GameObject* _parent);