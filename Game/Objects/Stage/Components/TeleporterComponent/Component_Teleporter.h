#pragma once
#include "../../Components/Component.h"
#include "../../../../../Engine/SceneManager.h"
#include "../../Stage.h"
#include "../../../../../EffekseeLib/EffekseerVFX.h"

enum ChangeType
{
	CHANGE_TELEPORT = 0,
	CHANGE_SCENE,
	CHANGE_JSON,
	CHANGE_Max,
};

class Component_Teleporter : public Component
{
private:
	bool isActive_;
	bool isTeleport_;


	XMFLOAT3 teleportPos_;
	SCENE_ID changeSceneID_;
	string changeJsonPath_;
	StageObject* target_;
	Component* playerBehavior_;

	Stage* pStage_;

	ChangeType changeType_;

	// effekseer: 変形行列
	std::shared_ptr<EFFEKSEERLIB::EFKTransform> mt;/*★★★*/
	std::vector<std::string> effectNames_;
	std::string effectType_;
public:
		/// <summary>
	    /// コンストラクタ
	 	/// </summary>
	 	/// <param name="_holder">コンポーネントの保持者</param>
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
	 	/// 解放
	 	/// </summary>
	 	void Release() override;
	 
	 	/// <summary>
	 	/// 保存
	 	/// </summary>
	 	/// <param name="_saveObj">データの保存情報</param>
	 	void Save(json& _saveObj) override;
	 
	 	/// <summary>
	 	/// 読込
	 	/// </summary>
	 	/// <param name="_loadObj">データの読込情報</param>
	 	void Load(json& _loadObj) override;
	 
	 	/// <summary>
	 	/// ImGuiパネル表示
	 	/// </summary>
	 	void DrawData()override;
	 
	 	/// <summary>
	 	/// テレポート
	 	/// </summary>
	 	void Teleport();	

		/// <summary>
		/// 実行
		/// </summary>
		/// <param name="_ch">どの形式で変化するか</param>
		void Execute(ChangeType _ch);

		/// <summary>
		/// 
		/// </summary>
		/// <param name="_target"></param>
		void SetTarget(StageObject* _target) { target_ = _target; }
};

