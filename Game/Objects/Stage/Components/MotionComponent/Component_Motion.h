#pragma once
#include "../Component.h"
#include "../../Components/BehaviorComponents/Component_PlayerBehavior.h"
#include <map>

struct MotionData {
    string filePath;    // ファイルパス
    int modelHandle;    // モデルハンドル
    int startFrame;     // 開始フレーム
    int endFrame;       // 終了フレーム
    int speed;          // アニメーションスピード
    bool isLoop;        // ループするか

    /// <summary> コンストラクタ </summary>
    MotionData(string _filePath, int _startFrame, int _endFrame, int _speed,bool _isLoop);

    /// <summary> デフォルトコンストラクタ </summary>
    MotionData() :filePath(""), modelHandle(-1), startFrame(0), endFrame(0), speed(0),isLoop(false) {}
};

class Component_Motion : public Component
{
protected:
    // モデルのハンドルリスト
    // FIX: PlayerState を参照するのは依存関係が高すぎる為修正が必要
	std::map<PlayerState, MotionData>modelHandleList_;

public:
    /// <summary> コンストラクタ </summary>
	Component_Motion(string _name, StageObject* _holder,ComponentType _type, Component* _parent);
	
    /// <summary> 初期化 </summary>
    void Initialize() override;
	
    /// <summary> 更新 </summary>
    void Update() override;

    /// <summary> 解放 </summary>
	void Release() override;

    /// <summary> ImGuiパネル表示 </summary>
	void DrawData() override;
};

