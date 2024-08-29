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
	// �K�[�h�R���C�_�[�̒ǉ�
   guardCollider_ = new BoxCollider(XMFLOAT3(0,0,0),XMFLOAT3(1,1,1));
   holder_->AddCollider(guardCollider_);
}

void Component_Guard::Update()
{

	if (isActive_) {

		// stage�����擾
		Stage* pStage = (Stage*)holder_->FindObject("Stage");
		if (pStage == nullptr)return;
		auto stageObj = pStage->GetStageObjects();

		for (auto object : stageObj) {
			// ���̃I�u�W�F�N�g�������Ă�R���C�_�[���擾
			std::list<Collider*>colliderList = object->GetColliderList();

			for (auto collider : colliderList) {
				// ���R���C�_�[�̈ʒu���擾
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

				// �����A�x�N�g���̒������ΏۃR���C�_�[�̔��a+�K�[�h�R���C�_�[�̔��a��菬����������
				if ((targetColliderSize.x + guardColliderSize.x + JUST_GUARD_DISTANCE > length) &&
					(length > targetColliderSize.x + guardColliderSize.x)){
					collider->GetGameObject()->KillMe();
					ImGui::Text("just");
					// �ϐ��㏸
					// just!
				}
				else if ((length > targetColliderSize.x + guardColliderSize.x) &&
					(targetColliderSize.x + guardColliderSize.x + SUCCESS_GUARD_DISTANCE > length)) {
					collider->GetGameObject()->KillMe();
					ImGui::Text("success");
					// �ϐ��㏸
					// success!
				}
			}
		}
		// ���R���C�_�[�Ƃ̋������v�Z
		// �ΏۃR���C�_�[�̈ʒu�x�N�g�� - �K�[�h�R���C�_�[�̈ʒu�x�N�g��
		// ���̋�����
		// �ΏۃR���C�_�[�̔��a+�K�[�h�R���C�_�[�̔��a < length < �ΏۃR���C�_�[�̔��a+�K�[�h�R���C�_�[�̔��a+��苗��
		// ��������just
		// �ΏۃR���C�_�[�̔��a+�K�[�h�R���C�_�[�̔��a+��苗�� < length < ��苗��
		// ��������success
		// ��苗���ȓ��ɂ���ꍇ�͖h�䐬��
		// �W���X�g�h�䐬�����̓_���[�W���󂯂Ȃ�
		// �h�䐬�����̓Q�[�W�𑝉�(�����_�ł͕ϐ��̑��������ł���)
		// �W���X�g�h�䐬�����̓Q�[�W������ɑ���(�����_�ł͕ϐ��̑��������ł���)
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
