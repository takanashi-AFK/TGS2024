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
    // モデルのハンドルリストにモデルを追加
    modelHandleList_[PSTATE_WALK] = MotionData("Models/Player/Running.fbx", 0, 40, 1);
    modelHandleList_[PSTATE_SHOOT] = MotionData("Models/Player/Fireball.fbx", 0, 150, 1);
    modelHandleList_[PSTATE_IDLE] = MotionData("Models/Player/Silly Dancing.fbx", 0, 200, 1);
    modelHandleList_[PSTATE_DODGE] = MotionData("Models/Player/Female Action Pose.fbx", 0, 60, 1);
    modelHandleList_[PSATE_DEAD] = MotionData("Models/Player/Standing React Death Right.fbx", 0, 106, 1);
}

void Component_PlayerMotion::Update()
{
    // プレイヤーの状態を取得 FIX: playerBehaviorが複数持たせないようにする
    PlayerState state = PSTATE_MAX;
    for (auto playerBehavior : holder_->FindComponent(PlayerBehavior)) state = ((Component_PlayerBehavior*)playerBehavior)->GetState();

    switch (state)
    {
    case PSTATE_IDLE: IdleMotion(); break;
    case PSTATE_WALK: WalkMotion(); break;
    case PSTATE_SHOOT: ShootMotion(); break;
    case PSTATE_DODGE: DodgeMotion(); break;
    case PSATE_DEAD: DeadMotion(); break;
    }

    // 現在のフレームをインクリメント
    currentFrame_++;

	// アニメーションの終了フレームに達したらフレームをリセット
    if (currentFrame_ == animationEndFrame_) {
        currentFrame_ = 0;
        isAnimationEnd_ = true;
    }

    ImGui::Text("nowModelHandle : %d", ((StageObject*)holder_)->GetModelHandle());
    ImGui::Text("currentFrame_ : %d", currentFrame_);
}

void Component_PlayerMotion::Release()
{
}

void Component_PlayerMotion::DrawData()
{
}

int Component_PlayerMotion::GetNowFrame()
{
    // プレイヤーの状態を取得 FIX: playerBehaviorが複数持たせないようにする
    PlayerState state = PSTATE_MAX;
    for (auto playerBehavior : holder_->FindComponent(PlayerBehavior)) state = ((Component_PlayerBehavior*)playerBehavior)->GetState();

    return Model::GetAnimFrame(modelHandleList_[state].modelHandle);
}

void Component_PlayerMotion::IdleMotion()
{
    // 終了フレームを設定
    animationEndFrame_ = 200;

    // 現在のモデル番号が待機モーションのモデル番号と違う場合...
    if (holder_->GetModelHandle() != modelHandleList_[PSTATE_IDLE].modelHandle) {

        // モデルを待機モーションのモデルに変更
        holder_->SetModelHandle(modelHandleList_[PSTATE_IDLE].modelHandle);
        
        // モデルが変わったときにフレームをリセット
        currentFrame_ = 0;

        // アニメーション終了フラグを下す
        isAnimationEnd_ = false;
    }

    // 現在のフレームが開始フレームと同じ場合
    if (currentFrame_ == 0) {

        // アニメーションを再生
        holder_->PlayAnimation(0, animationEndFrame_, 1);
    }
}

void Component_PlayerMotion::WalkMotion()
{
    // 終了フレームを設定
    animationEndFrame_ = 40;

    // 現在のモデル番号が歩行モーションのモデル番号と違う場合...
    if (holder_->GetModelHandle() != modelHandleList_[PSTATE_WALK].modelHandle) {

        // モデルを歩行モーションのモデルに変更
        holder_->SetModelHandle(modelHandleList_[PSTATE_WALK].modelHandle);

        // モデルが変わったときにフレームをリセット
        currentFrame_ = 0;

        // アニメーション終了フラグを下す
        isAnimationEnd_ = false;

    }

    // 現在のフレームが１フレーム前のフレームと同じ場合
    if (currentFrame_ == previousFrame_) {

        // アニメーションを再生
        holder_->PlayAnimation(previousFrame_, animationEndFrame_, 1);
    }

    // １フレーム前のフレームに現在のフレームを代入
    previousFrame_ = currentFrame_;

    // 途中で別Stateに移行した場合、
    // Modelクラスに存在するGetAnimFrame関数を使ってアニメーションのフレームを取得し、
}

void Component_PlayerMotion::ShootMotion()
{
    // 終了フレームを設定
    animationEndFrame_ = 150;

    // 現在のモデル番号が射撃モーションのモデル番号と違う場合...
    if (holder_->GetModelHandle() != modelHandleList_[PSTATE_SHOOT].modelHandle) {

        // モデルを射撃モーションのモデルに変更
        holder_->SetModelHandle(modelHandleList_[PSTATE_SHOOT].modelHandle);

        // モデルが変わったときにフレームをリセット
        currentFrame_ = 0;

        // アニメーション終了フラグを下す
        isAnimationEnd_ = false;
    }

    // 現在のフレームが開始フレームと同じ場合
    if (currentFrame_ == 0) {

        // アニメーションを再生
        holder_->PlayAnimation(0, animationEndFrame_, 1);
    }
}

void Component_PlayerMotion::DodgeMotion()
{
    // 終了フレームを設定
    animationEndFrame_ = 400;

    // 現在のモデル番号が回避モーションのモデル番号と違う場合...
    if (holder_->GetModelHandle() != modelHandleList_[PSTATE_DODGE].modelHandle) {

        // モデルを回避モーションのモデルに変更
        holder_->SetModelHandle(modelHandleList_[PSTATE_DODGE].modelHandle);
        
        // モデルが変わったときにフレームをリセット
        currentFrame_ = 0;

        // アニメーション終了フラグを下す
        isAnimationEnd_ = false;
    }

    // 現在のフレームが開始フレームと同じ場合
    if (currentFrame_ == 0) {

        // アニメーションを再生
        holder_->PlayAnimation(0, animationEndFrame_, 1);
    }
}

void Component_PlayerMotion::DeadMotion()
{
    // 終了フレームを設定
    animationEndFrame_ = 60;

    // 現在のモデル番号が回避モーションのモデル番号と違う場合...
    if (holder_->GetModelHandle() != modelHandleList_[PSATE_DEAD].modelHandle) {

        // モデルを回避モーションのモデルに変更
        holder_->SetModelHandle(modelHandleList_[PSATE_DEAD].modelHandle);

        // モデルが変わったときにフレームをリセット
        currentFrame_ = 0;

        // アニメーション終了フラグを下す
        isAnimationEnd_ = false;
    }

    // 現在のフレームが開始フレームと同じ場合
    if (currentFrame_ == 0) {

        // アニメーションを再生
        holder_->PlayAnimation(0, animationEndFrame_, 1);
    }
}
