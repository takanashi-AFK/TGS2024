#pragma once
#include "../Component.h"

#include <DirectXMath.h>

// usingディレクティブ
using namespace DirectX;

class Component_OnlyFall : public Component
{

private:
	bool isActive_;
	bool isEnd_;
	bool isInfinity_;
	float startHeight_;
	float fallSpeed_;
	float height_;
	float targetHeight_;
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="_holder">保有者</param>
	Component_OnlyFall(string _name, StageObject* _holder, Component* _parent);

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


	void Execute() { isActive_ = true; }

	void Stop() { isActive_ = false; }

	bool IsActive() { return isActive_; }
};

