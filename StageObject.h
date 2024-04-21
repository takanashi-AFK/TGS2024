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
    vector<Component*> myComponents_;

public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    StageObject();

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
    /// 使用するコンポーネントの初期化
    /// </summary>
    void Initialize();

    /// <summary>
    /// 使用するコンポーネントの更新
    /// </summary>
    void Update();
};