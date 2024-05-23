#pragma once

//インクルード
#include"../Component.h"
#include <DirectXMath.h>
using namespace DirectX;


//作成者:佐藤唯人
class Component_Chase:public Component
{
private:
	StageObject* target_;	//追従の対象オブジェクト
	float speed_;			//速度
	bool isActive_;			//追従が有効かどうか
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="_holder">保有者</param>
	Component_Chase(StageObject* _holder);

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
	/// 保存
	/// </summary>
	/// <param name="_saveobj">データの保存情報</param>
	void Save(json& _saveobj) override;

	/// <summary>
	/// 読み込み
	/// </summary>
	/// <param name="_loadobj">データの読込情報</param>
	void Load(json& _loadobj) override;

	void DrawData()override;

	// ターゲットの設定
	void SetTarget(StageObject* _target) { target_ = _target; }

	// 追従の開始
	void Start() { isActive_ = true; }

	// 追従の停止
	void Stop() { isActive_ = false; }

	// 追従が有効かどうか
	bool IsActive() { return isActive_; }

private:

	// 方向の計算
	XMVECTOR CalcDirection(XMFLOAT3 _holderPos, XMFLOAT3 _targetPos);

	// 距離を求める
	float CalcDistance(XMFLOAT3 _holderPos, XMFLOAT3 _targetPos);
	
	// ホルダーの向きを回転させる
	float CalcRotateAngle(XMVECTOR _direction);
	
	// 移動
	void Move(XMVECTOR _direction);
};

