#include "../../../../../Engine/ResourceManager/Model.h"
#include "Component_PlayerMotion.h"
#include "../../Stage.h"
#include "../../../../../Engine/ImGui/imgui.h"

Component_PlayerMotion::Component_PlayerMotion(string _name, StageObject* _holder,  Component* _parent)
	:Component_Motion(_name, _holder, PlayerMotion, _parent)
{
}

void Component_PlayerMotion::Initialize()
{
	motionModelMap_.insert(std::make_pair(PSTATE_WALK, Model::Load("Models/Player/Running.fbx")));
	// モデルのロード
	auto stageObjectList = ((Stage*)holder_)->GetStageObjects();
}

void Component_PlayerMotion::Update()
{
	static 	bool isAnimationNow_ = false;
	if (parent_ == nullptr)return;
	// 現在のStateを取得
	state_ = ((Component_PlayerBehavior*)parent_)->GetState();

	// ここうまくいってないから確認お願い
	if (state_ == PSTATE_WALK ) {
		// playerBehaviorのモデルハンドルを変える
		((StageObject*)parent_)->SetModelHandle(motionModelMap_[PSTATE_WALK]);

		// モーション再生
		if (isAnimationNow_ == false){
		Model::SetAnimFrame(((StageObject*)parent_)->GetModelHandle(), 0, 40, 1);
		isAnimationNow_ = true;
		}
		
	}
	else if(state_ != PSTATE_WALK) {
		isAnimationNow_ = false;
	}

	ImGui::Text(isAnimationNow_?"isAnimationNow_ :true":"isAnimationNow_ :false");
}

void Component_PlayerMotion::Release()
{
}

void Component_PlayerMotion::DrawData()
{

}

// playerStateのアドレスを取得
// 