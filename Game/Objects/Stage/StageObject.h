#pragma once

// インクルード
#include "../../../Engine/GameObject/GameObject.h"
#include "Components/Component.h"
#include <vector>
#include <DirectXMath.h>
// using宣言
using std::vector;

// ステージに登場するオブジェクトのクラス
class StageObject:public GameObject
{
protected:
    vector<Component*> myComponents_;   // 自身が保有するコンポーネント群
    string modelFilePath_;              // モデルのファイルパス
    int modelHandle_;                   // モデル番号
    DirectX::XMFLOAT3 localPosition_;
   
public:
    
    /// <summary>
    /// コンストラクタ
    /// </summary>
    StageObject(string _name,string _modelFilePath,GameObject* _parent);

    /// <summary>
    /// 使用するコンポーネントを追加
    /// </summary>
    /// <param name="_comp">使用するコンポーネントのアドレス</param>
    /// <returns>追加できたかどうか</returns>
    bool AddComponent(Component* _comp);

    /// <summary>
    /// 追加されたコンポーネントを削除
    /// </summary>
    /// <param name="_comp">削除するコンポーネントのアドレス</param>
    /// <returns>消去できたかどうか</returns>
    bool DeleteComponent(Component* _comp);

    /// <summary>
    /// 追加されたコンポーネントをすべて削除
    /// </summary>
    /// <returns>削除できたかどうか</returns>
    bool DeleteAllComponent();

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
    /// <param name="_saveObj">保存先のjsonオブジェクト</param>
    void Save(json& _saveObj);

    /// <summary>
    /// 読込
    /// </summary>
    /// <param name="_loadObj">読み込んだjsonオブジェクト</param>
    void Load(json& _loadObj);

    /// <summary>
    /// 自身が持っているデータをImGuiに表示する関数
    /// </summary>
    void DrawData();

    XMFLOAT3 GetLocalPosition() const;
    void SetLocalPosition(float x, float y, float z);
    
};

/// <summary>
/// ステージオブジェクトを生成する関数
/// </summary>
/// <param name="_name"> オブジェクト名</param>
/// <param name="_modelFilePath"> モデルのファイルパス</param>
/// <param name="_parent"> 親オブジェクト</param>
/// <returns>オブジェクトのアドレス</returns>
StageObject* CreateStageObject(string _name, string _modelFilePath, GameObject* _parent);