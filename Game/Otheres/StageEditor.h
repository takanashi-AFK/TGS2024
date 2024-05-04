#pragma once

// インクルード
#include "../../Engine/GameObject/GameObject.h"

// 前方宣言
class Stage;

// ステージエディターを管理するクラス
class StageEditor : public GameObject
{
private:
	Stage* editTarget_;
public:
	StageEditor(GameObject* _parent);
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;
	void DrawWorldOutLiner();

	void SetEditTarget(Stage* _editTarget) { editTarget_ = _editTarget; }
	void AddStageObject();
	void SaveStage();
	void LoadStage();
};

