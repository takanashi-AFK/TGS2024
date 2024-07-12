#pragma once

//インクルード
#include "../Component.h"
#include "../../StageObject.h"
#include "../DetectorComponents/Component_CircleRangeDetector.h"
#include "../../../../../EffekseeLib/EffekseerVFX.h"
#include "../MoveComponents/Component_WASDInputMove.h"
#include <DirectXMath.h>
#include <string>
using namespace DirectX;
class Component_Teleporter : public Component
{
private:
	enum TELEPORTERSTATE
	{
		TELEPORTSTART,
		TELEPORTING,
		TELEPORTEND,
	};
	TELEPORTERSTATE teleportState_;

	float scaleValue_;
	float lowerLimit_;
	float default_;
	StageObject* target_;
	string targetName_;
	XMFLOAT3 teleportPosition_; // テレポート先の座標
	Component_WASDInputMove* move_;
	// effekseer: 変形行列
	std::shared_ptr<EFFEKSEERLIB::EFKTransform> mt;/*★★★*/
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="_holder">保有者</param>
	Component_Teleporter(string _name, StageObject* _holder, Component* _parent);

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize() override;

	/// <summary>
	/// 更新
	/// </summary>
	void Update() override;

	/// <summary>
	/// 開放
	/// </summary>
	void Release() override;

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

	void TeleportStart();
	void Teleporting();
	void TeleportEnd();

};