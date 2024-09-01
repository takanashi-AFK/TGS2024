#pragma once

//インクルード
#include "../Component.h"

// effekseer: インクルード
#include "../../../../../EffekseeLib/EffekseerVFX.h"

class Component_BossBehavior : public Component
{
private:

	enum STATE { SHOT, TACKLE, SHOCK, WAIT, };	// 状態
	STATE nowState_;							// 現在の状態	
	STATE prevState_;							// １フレーム前の状態

	StageObject* target_;
	string targetName_;

	float shotrange_;
	float tacklerange_;
	float angle_;

	float shotRate_;
	float rotateSpeed_;
	float nextStateTime_;
	float shootHeight_;

	bool isActive_;

	// effekseer: 変形行列
	std::shared_ptr<EFFEKSEERLIB::EFKTransform> mt;/*★★★*/


	void RandomTransition(); // ランダム遷移のためのメソッド
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>	
	/// <param name="_holder">保有者</param>
	Component_BossBehavior(string _name, StageObject* _holder, Component* _parent);

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
	void Release() override;

	/// <summary>
	/// 衝突処理
	/// </summary>
	void OnCollision(GameObject* _target, Collider* _collider) override;

	/// <summary>
	/// 保存
	/// </summary>
	/// <param name="_saveObj">保存情報</param>
	void Save(json& _saveObj) override;

	/// <summary>
	/// 読込
	/// </summary>
	/// <param name="_loadObj">読込情報</param>
	void Load(json& _loadObj) override;

	/// <summary>
	/// ImGuiパネル表示
	/// </summary>
	void DrawData() override;

//------------ボスの行動メソッド----------------//

	/// <summary>
	/// 射撃
	/// </summary>
	void Shot();

	/// <summary>
	/// 突進
	/// </summary>
	void Tackle();

	/// <summary>
	/// 衝撃波(未実装) 浮かび上がり、急速に落下したときに発生する衝撃波ダメージの予定
	/// </summary>
	void Shock();

	/// <summary>
	/// 待機
	/// </summary>
	void Wait();					
};