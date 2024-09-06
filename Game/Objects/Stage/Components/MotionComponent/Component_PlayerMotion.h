#pragma once
#include "Component_Motion.h"
#include <vector>
#include "../../Components/BehaviorComponents/Component_PlayerBehavior.h"

class Component_PlayerMotion : public Component_Motion
{
private:
	int animationEndFrame_ = 0;
	int currentFrame_ = 0;
	bool isAnimationEnd_ = false;
	int previousFrame_ = 0;
public:
	/// <summary> コンストラクタ </summary>
	Component_PlayerMotion(string _name, StageObject* _holder, Component* _parent);
	
	/// <summary> 初期化 </summary>
	void Initialize() override;

	/// <summary> 更新 </summary>
	void Update() override;

	/// <summary> 解放 </summary>
	void Release() override;

	/// <summary> ImGuiパネル表示 </summary>
	void DrawData() override;
/*
getter :*/
	/// <summary> 現在のフレームを取得 </summary>
	int GetNowFrame();
/*
predicate :*/
	/// <summary> アニメーションが終了したか </summary>
	bool IsEnd() const { return isAnimationEnd_; }

private:
	/// <summary> 待機モーション </summary>
	void IdleMotion();

	/// <summary> 歩行モーション </summary>
	void WalkMotion();
	
	/// <summary> 射撃モーション </summary>
	void ShootMotion();
	
	/// <summary> 回避モーション </summary>
	void DodgeMotion();
	
	/// <summary> 死亡モーション </summary>
	void DeadMotion();
};

