#pragma once

// インクルード
#include "../../Engine/GameObject/GameObject.h"

// 前方宣言
class Stage;
class StageObject;

// ステージエディターを管理するクラス
class StageEditor : public GameObject
{
private:
	Stage* editStage_;

	// 編集対象
	int selectEditObjectIndex_;

public:
	StageEditor(GameObject* _parent);
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;

	void SetEditStage(Stage* _editStage) { editStage_ = _editStage; }
	void AddStageObject();
	void SaveStage();
	void LoadStage();

private:
	void DrawWorldOutLiner();
	void DrawDatails();
};

