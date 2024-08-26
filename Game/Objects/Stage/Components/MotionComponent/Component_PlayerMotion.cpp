//#include "../../../../../Engine/ResourceManager/Model.h"
//#include "Component_PlayerMotion.h"
//#include "../../Stage.h"
//#include "../../../../../Engine/ImGui/imgui.h"
//
//Component_PlayerMotion::Component_PlayerMotion(string _name, StageObject* _holder, Component* _parent)
//	:Component_Motion(_name, _holder, PlayerMotion, _parent), currentFrame_(0), animationEndFrame_(0), isAnimationEnd_(false)
//{
//}
//
//void Component_PlayerMotion::Initialize()
//{
//    motionModelMap_.insert(std::make_pair(PSTATE_WALK, Model::Load("Models/Player/Running.fbx")));
//    motionModelMap_.insert(std::make_pair(PSTATE_SHOOT, Model::Load("Models/Player/Fireball.fbx")));
//    motionModelMap_.insert(std::make_pair(PSTATE_IDLE, Model::Load("Models/Player/Silly Dancing.fbx")));
//    // ���f���̃��[�h
//    auto stageObjectList = ((Stage*)holder_)->GetStageObjects();
//}
//
//void Component_PlayerMotion::Update()
//{
//    if (playerBehavior_ == nullptr) {
//        playerBehavior_ = (Component_PlayerBehavior*)holder_->FindComponent("PlayerBehavior");
//    }
//
//	if (playerBehavior_ == nullptr) return;
//
//	state_ = playerBehavior_->GetState();
//    switch (state_)
//    {
//        // �ҋ@��Ԃ�������
//    case PSTATE_IDLE:
//		// �ҋ@��Ԃ̃A�j���[�V�����̏I���t���[����ݒ�
//        animationEndFrame_ = 200;
//		// ���f�����ҋ@��Ԃ̃��f������Ȃ�������ύX
//        if (((StageObject*)holder_)->GetModelHandle() != motionModelMap_[PSTATE_IDLE]) {
//            ((StageObject*)holder_)->SetModelHandle(motionModelMap_[PSTATE_IDLE]);
//            // ���f�����ς�����Ƃ��Ƀt���[�������Z�b�g
//            currentFrame_ = 0;  
//			isAnimationEnd_ = false;
//        }
//		// ���f�����ς�����Ƃ��ɃA�j���[�V�������Đ�
//        if (currentFrame_ == 0) {
//            holder_->PlayAnimation(0, animationEndFrame_, 1);
//        }
//        break;
//
//    case PSTATE_WALK:
//        animationEndFrame_ = 40;
//        if (((StageObject*)holder_)->GetModelHandle() != motionModelMap_[PSTATE_WALK]) {
//            ((StageObject*)holder_)->SetModelHandle(motionModelMap_[PSTATE_WALK]);
//            currentFrame_ = 0;  // ���f�����ς�����Ƃ��Ƀt���[�������Z�b�g
//            isAnimationEnd_ = false;
//
//        }
//        if (currentFrame_ == previousFrame_) {
//            holder_->PlayAnimation(previousFrame_, animationEndFrame_, 1);
//        }
//
//		previousFrame_ = currentFrame_;
//        // �r���ŕ�State�Ɉڍs�����ꍇ�A
//		// Model�N���X�ɑ��݂���GetAnimFrame�֐����g���ăA�j���[�V�����̃t���[�����擾���A
//
//        break;
//
//    case PSTATE_SHOOT:
//        animationEndFrame_ = 150;
//        if (((StageObject*)holder_)->GetModelHandle() != motionModelMap_[PSTATE_SHOOT]) {
//            ((StageObject*)holder_)->SetModelHandle(motionModelMap_[PSTATE_SHOOT]);
//            currentFrame_ = 0;  // ���f�����ς�����Ƃ��Ƀt���[�������Z�b�g
//            isAnimationEnd_ = false;
//        }
//        if (currentFrame_ == 0) {
//            holder_->PlayAnimation(0, animationEndFrame_, 1);
//        }
//        break;
//    }
//
//    // ���݂̃t���[�����C���N�������g
//    currentFrame_++;
//
//	// �A�j���[�V�����̏I���t���[���ɒB������t���[�������Z�b�g
//    if (currentFrame_ == animationEndFrame_) {
//        currentFrame_ = 0;
//        isAnimationEnd_ = true;
//    }
//
//    ImGui::Text("state_: %d", state_);
//    ImGui::Text("nowModelHandle : %d", ((StageObject*)holder_)->GetModelHandle());
//    ImGui::Text("currentFrame_ : %d", currentFrame_);
//}
//
//void Component_PlayerMotion::Release()
//{
//}
//
//void Component_PlayerMotion::DrawData()
//{
//}
