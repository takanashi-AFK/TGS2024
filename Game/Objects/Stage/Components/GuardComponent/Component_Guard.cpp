#include "../../../../../Engine/Collider/BoxCollider.h"
#include "../../../../../Engine/GameObject/GameObject.h"
#include "../../Stage.h"
#include "../../StageObject.h"
#include "Component_Guard.h"
#include <list>
#include "../../../../../Engine/ImGui/imgui.h"

namespace {
	const float JUST_GUARD_DISTANCE = 0.5f;
	const float SUCCESS_GUARD_DISTANCE = 2.f;
}

Component_Guard::Component_Guard(string _name, StageObject* _holder, Component* _parent)
	:Component(_holder, _name, Guard, _parent)
{
}

void Component_Guard::Initialize()
{
	// ガードコライダーの追加
   guardCollider_ = new BoxCollider(XMFLOAT3(0,0,0),XMFLOAT3(1,1,1));
   holder_->AddCollider(guardCollider_);
}

void Component_Guard::Update()
{

	if (isActive_) {

		// stage情報を取得
		Stage* pStage = (Stage*)holder_->FindObject("Stage");
		if (pStage == nullptr)return;
		auto stageObj = pStage->GetStageObjects();

		for (auto object : stageObj) {
			// そのオブジェクトが持ってるコライダーを取得
			std::list<Collider*>colliderList = object->GetColliderList();

			for (auto collider : colliderList) {
				// 他コライダーの位置を取得
				XMVECTOR originToTargetCollider;
				XMVECTOR originToGuardCollider;
				XMVECTOR vTargetToGuardCollider;

				XMFLOAT3 targetColliderPos = collider->GetCenter();
				XMFLOAT3 guardColliderPos = guardCollider_->GetCenter();

				originToGuardCollider = XMLoadFloat3(&guardColliderPos);
				originToTargetCollider = XMLoadFloat3(&targetColliderPos);
				vTargetToGuardCollider = originToTargetCollider - originToGuardCollider;

				float length = XMVectorGetX(XMVector3Length(vTargetToGuardCollider));

				XMFLOAT3 targetColliderSize = collider->GetSize();
				XMFLOAT3 guardColliderSize = guardCollider_->GetSize();

				// もし、ベクトルの長さが対象コライダーの半径+ガードコライダーの半径より小さかったら
				if ((targetColliderSize.x + guardColliderSize.x + JUST_GUARD_DISTANCE > length) &&
					(length > targetColliderSize.x + guardColliderSize.x)){
					collider->GetGameObject()->KillMe();
					ImGui::Text("just");
					// 変数上昇
					// just!
				}
				else if ((length > targetColliderSize.x + guardColliderSize.x) &&
					(targetColliderSize.x + guardColliderSize.x + SUCCESS_GUARD_DISTANCE > length)) {
					collider->GetGameObject()->KillMe();
					ImGui::Text("success");
					// 変数上昇
					// success!
				}
			}
		}
		// 他コライダーとの距離を計算
		// 対象コライダーの位置ベクトル - ガードコライダーの位置ベクトル
		// その距離が
		// 対象コライダーの半径+ガードコライダーの半径 < length < 対象コライダーの半径+ガードコライダーの半径+一定距離
		// だったらjust
		// 対象コライダーの半径+ガードコライダーの半径+一定距離 < length < 一定距離
		// だったらsuccess
		// 一定距離以内にいる場合は防御成功
		// ジャスト防御成功時はダメージを受けない
		// 防御成功時はゲージを増加(現時点では変数の増加だけでいい)
		// ジャスト防御成功時はゲージをさらに増加(現時点では変数の増加だけでいい)
	}
}

void Component_Guard::Release()
{
	holder_->ClearCollider();
}

void Component_Guard::DrawData()
{
	isActive_ ? ImGui::Text("true") : ImGui::Text("false");
}

void Component_Guard::Save(json& _saveObj)
{
}

void Component_Guard::Load(json& _loadObj)
{
}
