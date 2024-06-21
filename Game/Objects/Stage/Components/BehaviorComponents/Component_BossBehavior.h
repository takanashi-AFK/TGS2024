#pragma once

//インクルード
#include "../Component.h"

// effekseer: インクルード
#include "../../../../../EffekseeLib/EffekseerVFX.h"

class Component_BossBehavior : public Component
{
private:

	enum STATE { SHOT, TACKLE, SHOCK, WAIT, };	// 状態
	STATE nowState_;					// 現在の状態	
	STATE prevState_;					// １フレーム前の状態

	StageObject* target_;
	string targetName_;

	float shotrange_;
	float tacklerange_;

	float shotRate_;
	float rotateSpeed_;
	float nextStateTime_;

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
	void OnCollision(GameObject* _target) override;

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

	void Shot();

	void Tackle();

	void Shock();

	void Wait();					// 待機
};