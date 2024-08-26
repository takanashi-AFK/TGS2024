#pragma once
#include "../Component.h"
#include "../StateComponents/StateObserver.h"
#include "../StateComponents/Component_StateManager.h"


class Component_InputMove : public Component , StateObserver
{
private:
	bool isMove_;	// 移動中かどうか
	bool isEntryObserver_;	// オブザーバー登録フラグ
public:
	// コンストラクタ
	Component_InputMove(string _name, StageObject* _holder, Component* _parent);

	// 初期化
	void Initialize() override;

	// 更新
	void Update() override;

	// 更新
	void Release() override;

	// 保存
	void Save(json& _saveObj) override;

	// 読込
	void Load(json& _loadObj) override;

	// ImGuiパネル表示
	void DrawData() override;

	// 状態変更通知
	void OnStateChange(Component_StateManager* _stateManager) override;
};

