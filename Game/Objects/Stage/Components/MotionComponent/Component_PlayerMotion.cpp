#include "../../../../../Engine/ResourceManager/Model.h"
#include "Component_PlayerMotion.h"
#include "../../Stage.h"
#include "../../../../../Engine/ImGui/imgui.h"

Component_PlayerMotion::Component_PlayerMotion(string _name, StageObject* _holder, Component* _parent)
	:Component_Motion(_name, _holder, PlayerMotion, _parent), currentFrame_(0), animationEndFrame_(0), isAnimationEnd_(false)
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
    if (playerBehavior_ == nullptr) {
        playerBehavior_ = (Component_PlayerBehavior*)holder_->FindComponent("PlayerBehavior");
    }

	if (playerBehavior_ == nullptr) return;

	state_ = playerBehavior_->GetState();
    switch (state_)
    {
        // 待機状態だったら
    case PSTATE_IDLE:
		// 待機状態のアニメーションの終了フレームを設定
        animationEndFrame_ = 200;
		// モデルが待機状態のモデルじゃなかったら変更
        if (((StageObject*)holder_)->GetModelHandle() != motionModelMap_[PSTATE_IDLE]) {
            ((StageObject*)holder_)->SetModelHandle(motionModelMap_[PSTATE_IDLE]);
            // モデルが変わったときにフレームをリセット
            currentFrame_ = 0;  
			isAnimationEnd_ = false;
        }
		// モデルが変わったときにアニメーションを再生
        if (currentFrame_ == 0) {
            holder_->PlayAnimation(0, animationEndFrame_, 1);
        }
        break;

    case PSTATE_WALK:
        animationEndFrame_ = 40;
        if (((StageObject*)holder_)->GetModelHandle() != motionModelMap_[PSTATE_WALK]) {
            ((StageObject*)holder_)->SetModelHandle(motionModelMap_[PSTATE_WALK]);
            currentFrame_ = 0;  // モデルが変わったときにフレームをリセット
            isAnimationEnd_ = false;

        }
        if (currentFrame_ == previousFrame_) {
            holder_->PlayAnimation(previousFrame_, animationEndFrame_, 1);
        }

		previousFrame_ = currentFrame_;
        // 途中で別Stateに移行した場合、
		// Modelクラスに存在するGetAnimFrame関数を使ってアニメーションのフレームを取得し、

        break;

    case PSTATE_SHOOT:
        animationEndFrame_ = 150;
        if (((StageObject*)holder_)->GetModelHandle() != motionModelMap_[PSTATE_SHOOT]) {
            ((StageObject*)holder_)->SetModelHandle(motionModelMap_[PSTATE_SHOOT]);
            currentFrame_ = 0;  // モデルが変わったときにフレームをリセット
            isAnimationEnd_ = false;
        }
        if (currentFrame_ == 0) {
            holder_->PlayAnimation(0, animationEndFrame_, 1);
        }
        break;
    }

    // 現在のフレームをインクリメント
    currentFrame_++;

	// アニメーションの終了フレームに達したらフレームをリセット
    if (currentFrame_ == animationEndFrame_) {
        currentFrame_ = 0;
        isAnimationEnd_ = true;
    }

    ImGui::Text("state_: %d", state_);
    ImGui::Text("nowModelHandle : %d", ((StageObject*)holder_)->GetModelHandle());
    ImGui::Text("currentFrame_ : %d", currentFrame_);
}

void Component_PlayerMotion::Release()
{
}

void Component_PlayerMotion::DrawData()
{
}
