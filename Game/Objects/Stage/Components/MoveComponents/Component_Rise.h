#pragma once
#include "../Component.h"

#include <DirectXMath.h>

// usingディレクティブ
using namespace DirectX;

class Component_Rise : public Component
{
private:
	bool isInfinity_;
	bool isFirst_;
	bool isEnd_;
	float height_;
	float riseSpeed_;
	float targetHeight_;
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="_holder">保有者</param>
	Component_Rise(string _name, StageObject* _holder, Component* _parent);

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

	void SetInfinity(bool _isInfinity) { isInfinity_ = _isInfinity; }

	bool IsActive() { return isActive_; }

	bool IsEnd() { return isEnd_; }

	void SetIsEnd(bool _isEnd) { isEnd_ = _isEnd; }
};

