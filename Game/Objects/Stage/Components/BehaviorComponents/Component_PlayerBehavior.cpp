﻿#include "Component_PlayerBehavior.h"

// インクルード
#include "../../../../../Engine/Collider/BoxCollider.h"
#include "../../../../../Engine/Collider/SphereCollider.h"
#include "../../../../../Engine/DirectX/Direct3D.h"
#include "../../../../../Engine/DirectX/Input.h"
#include "../../../../../Engine/GameObject/Camera.h"
#include "../../Stage.h"
#include "../../StageObject.h"
#include "../../SkySphere.h"
#include "../AttackComponents/Component_MeleeAttack.h"
#include "../AttackComponents/Component_ShootAttack.h"
#include "../GaugeComponents/Component_HealthGauge.h"
#include "../MoveComponents/Component_WASDInputMove.h"
#include "../TimerComponent/Component_Timer.h"
#include "../MotionComponent/Component_PlayerMotion.h"
#include "../GuardComponent/Component_Guard.h"
#include <algorithm> 
#include "../../../../../Game/Objects/Stage/Components/GaugeComponents/Component_HealthGauge.h"
#include "../../../../../Engine/ImGui/imgui.h"


struct CompareDist {
    bool operator()(const RayCastData& lhs, const RayCastData& rhs) const {
        return lhs.dist < rhs.dist;
    }
};

Component_PlayerBehavior::Component_PlayerBehavior(string _name, StageObject* _holder, Component* _parent)
    : Component(_holder, _name, PlayerBehavior, _parent)
{
}

void Component_PlayerBehavior::Initialize()
{
    // コライダーの追加
    holder_->AddCollider(new BoxCollider(XMFLOAT3(0, 0, 0), XMFLOAT3(1, 1, 1)));

    holder_->SetScale(XMFLOAT3(0.5f, 0.5f, 0.5f));

    // 子コンポーネントの追加
    if (FindChildComponent("InputMove") == false)AddChildComponent(CreateComponent("InputMove", WASDInputMove, holder_, this));
    if (FindChildComponent("MeleeAttack") == false)AddChildComponent(CreateComponent("MeleeAttack", MeleeAttack, holder_, this));
    if (FindChildComponent("ShootAttack") == false)AddChildComponent(CreateComponent("ShootAttack", ShootAttack, holder_, this));
    if (FindChildComponent("Timer") == false)AddChildComponent(CreateComponent("Timer", Timer, holder_, this));
    if (FindChildComponent("HealthGauge") == false)AddChildComponent(CreateComponent("PlayerHealthGauge", HealthGauge, holder_, this));
    if (FindChildComponent("PlayerMotion") == false)AddChildComponent(CreateComponent("PlayerMotion", PlayerMotion, holder_, this));
	if (FindChildComponent("Guard") == false)AddChildComponent(CreateComponent("Guard", ComponentType::Guard, holder_, this));
}

void Component_PlayerBehavior::Update()
{
    auto hm = dynamic_cast<Component_HealthGauge*>(GetChildComponent("PlayerHealthGauge"));
    if (hm == nullptr)return;

    // 進捗を0.0〜1.0の範囲で計算
    float progress = hm->GetNow() / hm->GetMax();

    if (ImGui::Button("dead"))hm->TakeDamage(1000);



    auto timer = dynamic_cast<Component_Timer*>(GetChildComponent("Timer"));
    if (timer == nullptr) return;

    auto melee = dynamic_cast<Component_MeleeAttack*>(GetChildComponent("MeleeAttack"));
    if (melee == nullptr)return;

    auto move = dynamic_cast<Component_WASDInputMove*>(GetChildComponent("InputMove"));
    if (move == nullptr)return;



    switch (nowState)
    {
    case PSTATE_IDLE:
        Idle();  break;
    case PSTATE_WALK:
        Walk();  break;
    case PSTATE_WALKANDSHOOT:
        WalkAndShoot(); break;
    case PSTATE_MELEE:
        Melee(); break;
    case PSTATE_SHOOT:
        Shoot(); break;
    case PSTATE_GUARD:
		Guard(); break;
    default:
        break;
    }

}

void Component_PlayerBehavior::Release()
{
	holder_->ClearCollider();
}

void Component_PlayerBehavior::DrawData()
{
    ImGui::Text("%f,%f,%f,%f", frontVec_.m128_f32);
    auto timer = dynamic_cast<Component_Timer*>(GetChildComponent("Timer"));
    if (timer == nullptr)return;
    ImGui::Text("%f", timer->GetNowTime());

    if (ImGui::Button("Idle")) SetState(PSTATE_IDLE);
    if (ImGui::Button("Walk")) SetState(PSTATE_WALK);
    if (ImGui::Button("WalkAndShoot")) SetState(PSTATE_WALKANDSHOOT);
    if (ImGui::Button("Melee")) SetState(PSTATE_MELEE);
    if (ImGui::Button("Shoot")) SetState(PSTATE_SHOOT);

}

void Component_PlayerBehavior::OnCollision(GameObject* _target, Collider* _collider)
{
}

void Component_PlayerBehavior::Idle()
{
    auto move = dynamic_cast<Component_WASDInputMove*>(GetChildComponent("InputMove"));
    if (move == nullptr)return;

    if (move->GetIsMove()) {
        SetState(PSTATE_WALK);
    }
    else if (Input::IsMouseButton(1) && Input::IsMouseButtonDown(0) && nowState != PSTATE_WALK) {
        SetState(PSTATE_SHOOT);
    }
    else if (Input::IsMouseButtonDown(0)) {
        SetState(PSTATE_MELEE);
    }
    ImGui::Text("idle");

    // 死んだら死
}

void Component_PlayerBehavior::Walk()
{
    auto move = dynamic_cast<Component_WASDInputMove*>(GetChildComponent("InputMove"));
    if (move == nullptr)return;


    static bool prevAnim = false;
    if (move->GetIsMove() == true) {
        ImGui::Text("Move");
        if (Input::IsMouseButton(1) && Input::IsMouseButtonDown(0)) {
            SetState(PSTATE_WALKANDSHOOT);
        }
        else if (Input::IsMouseButtonDown(0)) {
            SetState(PSTATE_MELEE);
        }
    }
    else{
        SetState(PSTATE_IDLE);
    }
    ImGui::Text("Walk");

}

void Component_PlayerBehavior::WalkAndShoot()
{
    ShootExe();
    SetState(PSTATE_IDLE);
    ImGui::Text("WalkAndShoot");
}

void Component_PlayerBehavior::WalkAndMelee()
{
}

void Component_PlayerBehavior::Melee()
{
    auto move = dynamic_cast<Component_WASDInputMove*>(GetChildComponent("InputMove"));
    if (move == nullptr)return;
    auto melee = dynamic_cast<Component_MeleeAttack*>(GetChildComponent("MeleeAttack"));
    if (melee == nullptr)return;

    frontVec_ = move->GetMoveDirection();
    melee->SetForward(frontVec_);
    melee->Execute();

    SetState(PSTATE_IDLE);
    ImGui::Text("Melee");
}

void Component_PlayerBehavior::Shoot()
{

    auto motion = dynamic_cast<Component_PlayerMotion*>(GetChildComponent("PlayerMotion"));
    if (motion == nullptr)return;

    static bool isShoot = false;

    if (isShoot == false) {
        ShootExe();
        isShoot = true;
    }
    // アニメーションが終わったらState変更
    if (motion->IsEndAnimation()) {
        isShoot = false;
        SetState(PSTATE_IDLE);
    }
    ImGui::Text("shoot");
}

void Component_PlayerBehavior::Guard()
{
	auto guard = dynamic_cast<Component_Guard*>(GetChildComponent("Guard"));
	if (guard == nullptr)return;

	if (Input::IsKeyDown(DIK_SPACE)) {
		guard->Execute();
	}
	else {
		guard->Stop();
	}
}

void Component_PlayerBehavior::ShootExe()
{
    auto shoot = dynamic_cast<Component_ShootAttack*>(GetChildComponent("ShootAttack"));
    if (shoot == nullptr) return;

    if (target_ == nullptr) target_ = (StageObject*)holder_->FindObject(targetName_);

    XMVECTOR sightLine = Camera::GetSightLine();
    XMFLOAT3 camPos = Camera::GetPosition();
    // 枠内にいるENEMY属性を持ったStageObjectをターゲットにする

    XMVECTOR shootDir = { 0, 0, 0, 0 };
    Stage* pStage = ((Stage*)holder_->FindObject("Stage"));
    if (pStage == nullptr) return;

    auto stageObj = pStage->GetStageObjects();
    StageObject* hitObject = nullptr;
    XMFLOAT3 hitPosition{};
    // すべてのオブジェクトに対してレイを飛ばす
    for (auto obj : stageObj) {
        if (obj->GetObjectName() == holder_->GetObjectName()) continue;

        int hGroundModel = obj->GetModelHandle();
        if (hGroundModel < 0) continue;

        RayCastData data;
        data.start = camPos;  // レイの発射位置 カメラの位置のためworld座標

        XMStoreFloat3(&data.dir, XMVector3Normalize(sightLine)); // レイの方向 単位ベクトルのため、座標系に依存しないものと考える

        Model::RayCast(obj->GetModelHandle(), &data);  // レイを発射

        // レイが当たったら
        if (data.hit) {
            // 命中したオブジェクトが何か
            // hitObject = obj;

            XMVECTOR hitPosWorld = XMVector3TransformCoord(XMLoadFloat3(&data.pos), obj->GetWorldMatrix());

            XMStoreFloat3(&data.pos, hitPosWorld);
            rayHitObjectList_.push_back(data);
        }
    }

    // リストが空なら
    if (rayHitObjectList_.empty()) {
        shootDir = sightLine;
    }
    else {
        // 配列の中身を比較して最も近いものを取得
        // プレイヤーの位置からの距離を計算し、shootDirに代入
        auto min_iter = std::min_element(rayHitObjectList_.begin(), rayHitObjectList_.end(), CompareDist());

        // イテレータが有効か確認して最小要素の dist を出力
        if (min_iter != rayHitObjectList_.end()) {
            XMFLOAT3 holderPos = holder_->GetPosition();
            shootDir = XMVector3Normalize(XMLoadFloat3(&min_iter->pos) - XMLoadFloat3(&holderPos));
        }
        rayHitObjectList_.clear();
    }

    // 発射位置を設定
    XMFLOAT3 shootPosition = holder_->GetPosition();
    shootPosition.y += shootHeight_;
    shoot->SetShootingPosition(shootPosition);
    shoot->SetShootingDirection(shootDir);
    shoot->SetShootingSpeed(2.f);
    shoot->Execute();
    shootDir = {};
}



bool Component_PlayerBehavior::IsDead()
{
    auto hg = dynamic_cast<Component_HealthGauge*>(GetChildComponent("PlayerHealthGauge"));
    if (hg == nullptr)return false;

    return hg->IsDead();
}

//bool Component_PlayerBehavior::IsEnemyInRect(StageObject* _target)
//{
//
//	if (_target == nullptr) return false;
//	XMFLOAT3 pos = ConvertTo2DPos(_target);
//
//	float left = -0.8f;    // 左の境界
//	float right = 0.8f;    // 右の境界
//	float top = 0.8f;      // 上の境界
//	float bottom = -0.8f;  // 下の境界
//	if (_target->GetAttribute() == ENEMY && pos.x <= left && pos.x >= right && pos.y <= bottom && pos.y >= top)
//		return true;
//	
//	return false;
//
//}
//
//XMFLOAT3 Component_PlayerBehavior::ConvertTo2DPos(StageObject* _target)
//{
//	int scWidth = Direct3D::screenWidth_;
//	int scHeight = Direct3D::screenHeight_;
//
//#ifdef _DEBUG
//	scWidth = scWidth * 0.7;
//	scHeight = scHeight * 0.7;
//#endif // _DEBUG
//
//	XMFLOAT3 targetPos = _target->GetPosition();
//
//	targetPos.x = (float)(targetPos.x * 2.0f) / (float)scWidth - 1.0f;
//	targetPos.y = 1.0f - (float)(targetPos.y * 2.0f) / (float)scHeight;
//	targetPos.z = 0.0f;
//
//	return targetPos;
//}
