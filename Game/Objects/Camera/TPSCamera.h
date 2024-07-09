#pragma once
#include "../../../Engine/GameObject/GameObject.h"
#include "../../../Engine/Json/JsonReader.h"

class TPSCamera : public GameObject
{
private:
	XMFLOAT2 angle_;
	float sensitivity_;
	GameObject* pTarget_;
	string targetName_;
	bool isActive_;
	float targetHeight_;
	float targetDistance_;
	XMVECTOR prevAxis_;
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="parent">親オブジェクト</param>
	TPSCamera(GameObject* parent);

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize() override;
	
	/// <summary>
	/// 更新
	/// </summary>
	void Update() override;
	
	/// <summary>
	/// 描画
	/// </summary>
	void Draw() override;
	
	/// <summary>
	/// 解放
	/// </summary>
	void Release() override;

	/// <summary>
	/// ImGui表示
	/// </summary>
	void DrawData();

	/// <summary>
	/// 保存
	/// </summary>
	/// <param name="saveObj">保存オブジェクト</param>
	void Save(json& saveObj);

	/// <summary>
	/// 読込
	/// </summary>
	/// <param name="loadObj">読込オブジェクト</param>
	void Load(json& loadObj);

	/// <summary>
	/// 実行状態の設定
	/// </summary>
	/// <param name="isActive"></param>
	void SetActive(bool isActive) { isActive_ = isActive; }
	
	/// <summary>
	/// 対象オブジェクトの設定
	/// </summary>
	/// <param name="target">対象オブジェクト</param>
	void SetTarget(GameObject* target) { pTarget_ = target; }
	
	/// <summary>
	/// 回転角度の取得
	/// </summary>
	/// <returns>回転角度</returns>
	XMFLOAT2 GetAngle() { return angle_; }
};

