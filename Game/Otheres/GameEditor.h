#pragma once

// インクルード
#include "../../Engine/GameObject/GameObject.h"

// 前方宣言
class Stage;
class StageObject;

class UIPanel;
class UIObject;

enum EditType
{
	STAGE,
	UIPANEL,
	NONE
};

// ステージエディターを管理するクラス
class GameEditor : public GameObject
{
private:
	Stage* editStage_;				// 編集対象のステージ
	int selectEditStageObjectIndex_;		// 選択中のステージオブジェクトのインデックス

	UIPanel* editUIPanel_;			// 編集パネル
	int selectEditUIObjectIndex_;		// 選択中のUIオブジェクトのインデックス
	
	EditType editType_;				// 編集対象の種類
public:
	GameEditor(GameObject* _parent);
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;

	void SetEditStage(Stage* _editStage) { editStage_ = _editStage; }
	void AddStageObject();
	void SaveStage();
	void LoadStage();

	void SetEditUIPanel(UIPanel* _editUIPanel) { editUIPanel_ = _editUIPanel; }
	void AddUIObject();
	void SaveUIPanel();
	void LoadUIPanel();

private:
	void DrawWorldOutLiner();
	void DrawStageOutLiner();
	void DrawUIPanelOutLiner();

	void DrawDatails();
	void DrawStageObjectDatails();
	void DrawUIObjectDatails();
};

