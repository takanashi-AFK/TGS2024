#pragma once

// インクルード
#include "../../../Engine/DirectX/Direct3D.h"
#include "../../../Engine/GameObject/GameObject.h"
#include "Components/Component.h"
#include <vector>

// using宣言
using std::vector;


class StageObject : public GameObject
{
protected:
	vector<Component*> myComponents_;   // 自身が保有するコンポーネント群

	string modelFilePath_;              // モデルのファイルパス
	int modelHandle_;                   // モデル番号

	bool isOnGround_;                   // 地面に設置するかどうか
	bool isCollisionWall_;              // 壁に当たったかどうか
	bool isColliding_;                  // ほかのオブジェクトと衝突するかどうか
	XMFLOAT3 onGroundOffset_;           // 地面に設置する際のオフセット
	float fallSpeed_;                   // 落下速度

	Direct3D::SHADER_TYPE shaderType_;   // シェーダータイプ
public:
	/// <summary> コンストラクタ </summary>
	StageObject(string _name,string _modelFilePath,GameObject* _parent);

	/// <summary> 初期化 </summary>
	void Initialize() override;

	/// <summary> 更新 </summary>
	void Update() override;

	/// <summary> 描画 </summary>
	void Draw() override;

	/// <summary> 解放 </summary>
	void Release() override;

	/// <summary> 衝突処理 </summary>
	void OnCollision(GameObject* _target, Collider* _collider) override;

	/// <summary> 保存 </summary>
	virtual void Save(json& _saveObj);

	/// <summary> 読込 </summary>
	virtual  void Load(json& _loadObj);

	/// <summary> ImGui表示 </summary>
	virtual void DrawData();

	/// <summary> コンポーネントの追加 </summary>
	bool AddComponent(Component* _comp);

	/// <summary> コンポーネントの削除 </summary>
	bool DeleteComponent(Component* _comp);

	/// <summary> 全コンポーネントの削除 </summary>
	bool DeleteAllComponent();

	/// <summary> コンポーネントを探す </summary>
	Component* FindComponent(string _name);
	vector<Component*> FindComponent(ComponentType _type);

	/// <summary> アニメーションを再生 </summary>
	void PlayAnimation(int _startFrame, int _endFrame, float _speed);
/*
getter :*/
	/// <summary> モデル番号の取得 </summary>
	int GetModelHandle() const { return modelHandle_; }

	/// <summary> モデルファイルパスの取得 </summary>
	string GetModelFilePath() const { return modelFilePath_; }

	/// <summary> 地面に設置する際のオフセットの取得 </summary>
	XMFLOAT3 GetOnGroundOffset() const { return onGroundOffset_; }

	/// <summary> 落下速度の取得 </summary>
	float GetFallSpeed() const { return fallSpeed_; }

	/// <summary> シェーダータイプの取得 </summary>
	Direct3D::SHADER_TYPE GetShaderType() const { return shaderType_; }

	/// <summary> 衝突するかどうかを取得 </summary>
	bool GetIsColliding() { return isColliding_; }
/*
setter :*/
	/// <summary> モデル番号の設定 </summary>
	void SetModelHandle(int _handle) { modelHandle_ = _handle; }

	/// <summary> モデルファイルパスの設定 </summary>
	void SetModelFilePath(string _path) { modelFilePath_ = _path; }

	/// <summary> 地面に設置する際のオフセットの設定 </summary>
	void SetOnGroundOffset(XMFLOAT3 _offset) { onGroundOffset_ = _offset; }

	/// <summary> 落下速度の設定 </summary>
	void SetFallSpeed(float _speed) { fallSpeed_ = _speed; }

	/// <summary> シェーダータイプの設定 </summary>
	void SetShader(Direct3D::SHADER_TYPE _type) { shaderType_ = _type; };
/*
predicate :*/
	/// <summary> 地面に設置するかどうかを判定 </summary>
	bool IsOnGround() const { return isOnGround_; }

	/// <summary> 壁に当たったかどうかを判定</summary>
	bool IsCollisionWall() const { return isCollisionWall_; }

private:
	/// <summary> 接地処理 </summary>
	void OnGround(float _fallSpeed);

	/// <summary> 壁めり込み防止処理 </summary>
	void CollisionWall();
};

/// <summary>
/// ステージオブジェクトを生成する関数
/// </summary>
/// <param name="_name"> オブジェクト名</param>
/// <param name="_modelFilePath"> モデルファイルパス</param>
/// <param name="_parent"> 親オブジェクト</param>
/// <returns>作成したオブジェクトのポインタ</returns>
StageObject* CreateStageObject(string _name, string _modelFilePath, GameObject* _parent);