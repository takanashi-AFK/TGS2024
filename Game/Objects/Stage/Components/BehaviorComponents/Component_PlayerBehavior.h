#pragma once
#include "../Component.h"
#include <DirectXMath.h>
#include "../../StageObject.h"
#include <vector>
#include "../../../../../Engine/ResourceManager/Model.h"

// プレイヤーの状態
enum PlayerState {
	PSTATE_IDLE = 0,	/* 待機 */
	PSTATE_WALK,		/* 歩行 */
	PSTATE_SHOOT,		/* 射撃 */
	PSTATE_DODGE,		/* 回避 */
	PSATE_DEAD,			/* 死亡 */
	PSTATE_MAX
	};

class CountDown;
class Component_PlayerBehavior : public Component
{
private:
	PlayerState nowState_, prevState_;	// 現在の状態、前の状態
	float shootHeight_;					// 射撃の高さ
	bool isGameStart_;					// ゲーム開始フラグ

public:
	/// <summary> コンストラクタ </summary>
	Component_PlayerBehavior(string _name,StageObject* _holder,Component* _parent);

	/// <summary> 初期化 </summary>
	void Initialize() override;

	/// <summary> 更新 </summary>
	void Update() override;

	/// <summary> 解放 </summary>
	void Release() override;
	
	/// <summary> 保存 </summary>
	void Save(json& _saveObj) override;

	/// <summary> 読込 </summary>
	void Load(json& _loadObj) override;

	/// <summary> ImGuiパネル表示 </summary>
	void DrawData() override;

/*
setter :*/
	/// <param name="_state"> プレイヤーの状態 </param>
	void SetState(PlayerState _state) { prevState_ = nowState_; nowState_ = _state; }

	/// <param name="_height"> 射撃の高さ </param>
	void SetShootHeight(float _height) { shootHeight_ = _height; }

	/// <param name="_flag"> ゲーム開始フラグ </param>
	void SetGameStart(bool _flag) { isGameStart_ = _flag; }

/*
getter :*/
	/// <returns> プレイヤーの状態 </returns>
	PlayerState GetState() const { return nowState_; }

	/// <returns> 前のプレイヤーの状態 </returns>
	PlayerState GetPrevState() const { return prevState_; }

	/// <returns> 射撃の高さ </returns>
	float GetShootHeight() const { return shootHeight_; }

	/// <returns> ゲーム開始フラグ </returns>
	bool GetGameStart() const { return isGameStart_; }

/*
predicate :*/
	/// <returns> プレイヤーが死んでいるか </returns>
	bool IsDead() const { return nowState_ == PSATE_DEAD; }

private:
	/// <summary> 射撃方向の計算 </summary>
	/// <returns> 射撃方向 </returns>
	XMVECTOR CalcShootDirection();

	/// <summary> 待機状態時の処理 </summary>
	void Idle();
	
	/// <summary> 歩行状態時の処理 </summary>
	void Walk();
	
	/// <summary> 射撃状態時の処理 </summary>
	void Shoot();

	/// <summary> 回避状態時の処理 </summary>
	void Dodge();

	/// <summary> 死亡状態時の処理 </summary>
	void Dead();
};

