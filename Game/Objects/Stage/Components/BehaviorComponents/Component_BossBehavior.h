#pragma once

//インクルード
#include "../Component.h"

// effekseer: インクルード
#include "../../../../../EffekseeLib/EffekseerVFX.h"

enum BossState{
	BOSS_STATE_IDLE = 0,
	BOSS_STATE_SHOT,
	BOSS_STATE_TACKLE,
	BOSS_STATE_DEAD,
	BOSS_STATE_MAX
};

class Component_BossBehavior : public Component
{
private:
	BossState nowState_;	// 現在の状態

	StageObject* target_;	// 対象
	string targetName_;		// 対象の名前

	float shotInterval_;		// 射撃間隔
	float stateChangeDelay_;	// 状態変更遅延
	float shootHeight_;			// 射撃の高さ
	bool isActive_;				// アクティブフラグ
	bool isGameStart_;			// ゲーム開始フラグ

	std::shared_ptr<EFFEKSEERLIB::EFKTransform> mt; // effekseer: モデルの位置情報

public:
	/// <summary> コンストラクタ </summary>
	Component_BossBehavior(string _name, StageObject* _holder, Component* _parent);

	/// <summary> 初期化 </summary>
	void Initialize() override;

	/// <summary> 更新 </summary>
	void Update() override;

	/// <summary> 解放 </summary>
	void Release() override;

	/// <summary> 衝突処理 </summary>
	void OnCollision(GameObject* _target, Collider* _collider) override;

	/// <summary> 保存 </summary>
	void Save(json& _saveObj) override;

	/// <summary> 読込 </summary>
	void Load(json& _loadObj) override;

	/// <summary> ImGuiパネル表示 </summary>
	void DrawData() override;

/*
setter :*/
	/// <param name="_state"> ボスの状態 </param>
	void SetState(BossState _state) { nowState_ = _state; }
/*
predicate:*/
	bool IsDead();

private:
	/// <summary> ランダムに状態を抽選する処理 </summary>
	BossState RandomStatePick();

	/// <summary> 射撃状態時の処理 </summary>
	void Shot();

	/// <summary> 突進状態時の処理 </summary>
	void Tackle();

	/// <summary> 待機状態時の処理 </summary>
	void Idle();	

	/// <summary> 死亡状態時の処理 </summary>
	void Dead();
};