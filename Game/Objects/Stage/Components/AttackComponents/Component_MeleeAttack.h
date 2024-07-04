#pragma once
#include "Component_Attack.h"
#include "../../../../../Engine/Collider/BoxCollider.h"

class Component_MeleeAttack : public Component_Attack
{
private:
	XMVECTOR forward_; //前方向
	XMVECTOR prevFrontVec_;
	bool isOneHit_;

	// 追記※
	XMVECTOR direction_;	// 攻撃方向
	XMFLOAT3 colliderSize_; // コライダーの大きさ
	bool isHit_;			// ヒットしたかどうか
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="_holder">保有者</param>
	/// <param name="_name">自身のコンポーネント名</param>
	/// <param name="_type">自身のコンポーネントタイプ</param>
	Component_MeleeAttack(string _name, StageObject* _holder, Component* _parent);

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize() override;


	/// <summary>
	/// 更新
	/// </summary>
	void Update() override;

	/// <summary>
	/// 解放
	/// </summary>
	void Release();

	/// <summary>
	/// ImGuiパネル表示
	/// </summary>
	void DrawData() override;

	/// <summary>
	/// 一定時間たったらコライダーを削除
	/// </summary>
	/// <param name="_time">何秒後に消すか</param>
	bool AutoDelete(float _time);

	/// <summary>
	/// 衝突判定
	/// </summary>
	/// <param name="_target"></param>
	void OnCollision(GameObject* _target) override;
	
	/// <summary>
	/// 正面方向の設定
	/// </summary>
	/// <param name="_forward">正面方向ベクトル</param>
	void SetForward(XMVECTOR _forward) { forward_ = _forward; }
};

