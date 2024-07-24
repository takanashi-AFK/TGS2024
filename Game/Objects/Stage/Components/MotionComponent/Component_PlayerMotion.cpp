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
	motionModelMap_.insert(std::make_pair(PSTATE_SHOOT, Model::Load("Models/Player/Fireball.fbx")));
	motionModelMap_.insert(std::make_pair(PSTATE_IDLE, Model::Load("Models/Player/Silly Dancing.fbx")));
	// モデルのロード
	auto stageObjectList = ((Stage*)holder_)->GetStageObjects();
}

void Component_PlayerMotion::Update()
{
	static bool prevAnim = false;
	if (parent_ == nullptr) return;
	// 現在のStateを取得
	state_ = ((Component_PlayerBehavior*)parent_)->GetState();

	if (state_ == PSTATE_WALK) {
		// playerBehaviorのモデルハンドルを変える
		((StageObject*)holder_)->SetModelHandle(motionModelMap_[PSTATE_WALK]);

		if (prevAnim == false) holder_->PlayAnimation(0, 40, 1);
		prevAnim = true;
	}
	else if (state_ == PSTATE_SHOOT) {
		((StageObject*)holder_)->SetModelHandle(motionModelMap_[PSTATE_SHOOT]);

		if (prevAnim == false)holder_->PlayAnimation(0, 101, 1);
		prevAnim = true;
		
	}
	else if (state_ == PSTATE_IDLE) {
		((StageObject*)holder_)->SetModelHandle(motionModelMap_[PSTATE_IDLE]);
		prevAnim = false;
		if (prevAnim == false)holder_->PlayAnimation(0, 150, 1);
	}
	else {
		prevAnim = false;
		holder_->PlayAnimation(0, 0, 1);
	}

	ImGui::Text("state_: %d", state_);
	ImGui::Text("nowModelHandle : %d", ((StageObject*)holder_)->GetModelHandle());
	ImGui::Text(prevAnim ? "isAnimationNow_ :true" : "isAnimationNow_ :false");
}

void Component_PlayerMotion::Release()
{
}

void Component_PlayerMotion::DrawData()
{

}

// playerStateのアドレスを取得
// 