#pragma once

//インクルード
#include"../Component.h"
#include <DirectXMath.h>
using namespace DirectX;


/// <summary>
/// ターゲットに対して追従するコンポーネントのクラス
/// </summary>
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
	Component_Chase(string _name, StageObject* _holder, Component* _parent);

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
	/// 読込
	/// </summary>
	/// <param name="_loadobj">データの読込情報</param>
	void Load(json& _loadobj) override;

	/// <summary>
	/// ImGuiパネル表示
	/// </summary>
	void DrawData()override;

	/// <summary>
	/// ターゲットの設定
	/// </summary>
	void SetTarget(StageObject* _target) { target_ = _target; }

	/// <summary>
	/// 追従の開始
	/// </summary>
	void Start() { isActive_ = true; }

	/// <summary>
	/// 追従の停止
	/// </summary>
	void Stop() { isActive_ = false; }

	/// <summary>
	/// 追従が有効かどうか
	/// </summary>
	bool IsActive() { return isActive_; }

private:

	/// <summary>
	/// 方向の計算
	/// </summary>
	XMVECTOR CalcDirection(XMFLOAT3 _holderPos, XMFLOAT3 _targetPos);

	/// <summary>
	/// 距離を求める
	/// </summary>
	float CalcDistance(XMFLOAT3 _holderPos, XMFLOAT3 _targetPos);
	
	/// <summary>
	/// ホルダーの向きを回転させる
	/// </summary>
	float CalcRotateAngle(XMVECTOR _direction);
	
	/// <summary>
	/// 移動
	/// </summary>
	void Move(XMVECTOR _direction);
};

