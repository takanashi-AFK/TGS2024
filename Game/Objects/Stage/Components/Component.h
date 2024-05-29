#pragma once

// インクルード
#include "../../../../Engine/Json/JsonReader.h"

// 前方宣言
class StageObject;

// using宣言
using std::vector;

// コンポーネントタイプ
enum ComponentType {
    Rotation,
    RotationY,
    RotationX,
    RotationZ,
    MoveX,
    HealthManager,
    Chase,
	CircleRangeDetector,
    FanRangeDetector,
    OtiBehavior,
    Timer,
    Fall,
    Attack,
    CactanAttack,
    // コンポーネント追加時に識別番号を追加
};

// コンポ―ネント基底クラス
class Component
{
protected:
    string name_;                           // コンポーネント名
    ComponentType type_;                    // コンポーネントタイプ
    StageObject* holder_;                   // コンポ―ネント保有者のポインタ
    vector<Component*> childComponents_;    // 子コンポーネント群

public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="_holder">保有者</param>
    /// <param name="_name">名前</param>
    Component(StageObject* _holder, string _name,ComponentType _type);

    /// <summary>
    /// 初期化処理を行う純粋仮想関数
    /// </summary>
    virtual void Initialize() = 0;

    /// <summary>
    /// 更新処理を行う純粋仮想関数
    /// </summary>
    virtual void Update() = 0;

    /// <summary>
    /// 開放処理を行う純粋仮想関数
    /// </summary>
    virtual void Release() = 0;

    /// <summary>
    /// jsonファイルに現在のデータを保存する純粋仮想関数
    /// </summary>
    /// <param name="_saveObj">保存情報</param>
    virtual void Save(json& _saveObj) = 0;

    /// <summary>
    /// jsonファイルに現在のデータを保存する純粋仮想関数
    /// </summary>
    /// <param name="_saveObj">読込情報</param>
    virtual void Load(json& _loadObj) = 0;

    /// <summary>
    /// コンポーネントが持っているデータをImGuiに表示する関数
    /// </summary>
    virtual void DrawData() {};

    /// <summary>
    /// 自身＆子コンポーネントを初期化
    /// </summary>
    void ChildIntialize();

	/// <summary>
	/// 自身＆子コンポーネントを更新
	/// </summary>
	void ChildUpdate();

    /// <summary>
    /// 自身＆子コンポーネントを解放
    /// </summary>
    void ChildRelease();

	/// <summary>
	/// 自身＆子コンポーネントを描画
	/// </summary>
	void ChildDrawData();

    /// <summary>
    /// 自身＆子コンポーネントを保存
    /// </summary>
    void ChildSave(json& _saveObj);

    /// <summary>
    /// 自身＆子コンポーネントを読込
    /// </summary>
    void ChildLoad(json& _loadObj);

    /// <summary>
    /// 子コンポーネントを追加
    /// </summary>
    /// <param name="comp"></param>
    bool AddChildComponent(Component* _comp);

    /// <summary>
    /// 子コンポーネントを削除
    /// </summary>
    /// <param name="comp"></param>
    bool DeleteChildComponent(Component* _comp);

    /// <summary>
    /// 子コンポーネントに該当のタイプのコンポーネントがあるかを探す
    /// </summary>
    /// <param name="_type"></param>
    /// <returns></returns>
    bool FindChildComponent(ComponentType _type);

/* getter: */

    /// <summary>
    /// 識別子を取得
    /// </summary>
    /// <returns>コンポーネント識別子</returns>
    ComponentType GetType() const { return type_; }

    /// <summary>
    /// 名前を取得
    /// </summary>
    /// <returns>コンポーネント名</returns>
    string GetName() { return name_; }

    /// <summary>
    /// 子コンポーネントを取得
    /// </summary>
    /// <param name="_type">識別子</param>
    /// <returns>子コンポーネント</returns>
    Component* GetChildComponent(ComponentType _type);
};

/// <summary>
///コンポーネントを作成する
/// </summary>
/// <param name="_type">コンポーネントタイプ</param>
/// <param name="_holder">保有者</param>
/// <returns>作成したコンポーネント</returns>
Component* CreateComponent(ComponentType _type,StageObject* _holder);