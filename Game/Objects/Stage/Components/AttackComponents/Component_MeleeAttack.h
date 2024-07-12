#pragma once
#include "Component_Attack.h"
#include "../../../../../Engine/Collider/BoxCollider.h"

class Component_MeleeAttack : public Component_Attack
{
private:
	XMVECTOR direction_;	// 攻撃方向
	XMFLOAT3 colliderSize_; // コライダーの大きさ
	bool isHit_;			// ヒットしたかどうか
	BoxCollider* collider_;
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
	/// 衝突判定
	/// </summary>
	/// <param name="_target"></param>
	void OnCollision(GameObject* _target, Collider* _collider) ;
	
	/// <summary>
	/// 攻撃方向の設定
	/// </summary>
	/// <param name="_direction"></param>
	void SetDirection(XMVECTOR _direction) { direction_ = _direction; }
};

