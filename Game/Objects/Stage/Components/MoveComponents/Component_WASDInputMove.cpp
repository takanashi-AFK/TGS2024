#include "Component_WASDInputMove.h"
#include "../../../../../Engine/directX/Input.h"
#include "../../../../../Engine/ImGui/imgui.h"
#include "../../StageObject.h"
#include "../../../../../Engine/GameObject/Camera.h"
#include "../../../../../Engine/GameObject/GameObject.h"
#include "../../../Camera/TPSCamera.h"
#include "../../../Game/Objects/Stage/Components/StateComponents/Component_StateManager.h"
namespace
{
	float speed = 0.1f;
}

Component_WASDInputMove::Component_WASDInputMove(string _name, StageObject* _holder, Component* _parent)
	:Component(_holder, _name, WASDInputMove, _parent), isMove_(false)
{
}

void Component_WASDInputMove::Initialize()
{
    // �C���^�[�t�F�[�X�̏�����
    StateObserver::Initialize(this->holder_);
}

void Component_WASDInputMove::Update()
{
    // ���̃R���|�[�l���g���A�N�e�B�u�łȂ��ꍇ�A�������I��
    if (!isActive_) return;
    isMove_ = false;
    // ��{�̃x�N�g����p�ӁA������
    dir_ = XMVectorZero();

    TPSCamera* tpsCamera = (TPSCamera*)holder_->FindObject("TPSCamera");
    if (tpsCamera == nullptr) return;

    XMFLOAT2 angle = tpsCamera->GetAngle();

    // �J�����̎����x�N�g�����擾�AY������0�ɂ��Đ��K��
    XMVECTOR sightLine = Camera::GetSightLine();
    sightLine = XMVectorSetY(sightLine, 0);
    sightLine = XMVector3Normalize(sightLine);

    // ���͂ɉ����ĕ����x�N�g����ݒ�
    if (Input::IsKey(DIK_W)) { dir_ += sightLine; isMove_ = true; holder_->SetRotateY(angle.y - 25); }
    if (Input::IsKey(DIK_A)) { dir_ += XMVector3Transform(sightLine, XMMatrixRotationY(XMConvertToRadians(-90))); isMove_ = true; holder_->SetRotateY((angle.y - 25) - 90); }
    if (Input::IsKey(DIK_S)) { dir_ += -sightLine; isMove_ = true; holder_->SetRotateY((angle.y - 25) + 180); }
    if (Input::IsKey(DIK_D)) { dir_ += XMVector3Transform(sightLine, XMMatrixRotationY(XMConvertToRadians(90))); isMove_ = true; holder_->SetRotateY((angle.y - 25) + 90);}
    dir_ = XMVector3Normalize(dir_);
    XMVECTOR move = dir_ * speed;

    // �ړ��x�N�g����XMFLOAT3�ɕϊ�
	XMFLOAT3 pos = holder_->GetPosition();
    XMStoreFloat3(&pos,XMLoadFloat3(&pos)+move);

    // �V�����ʒu��ݒ�
    holder_->SetPosition(pos);
}

void Component_WASDInputMove::Release()
{
}

void Component_WASDInputMove::DrawData()
{
	ImGui::Checkbox("Active", &isActive_);
	ImGui::SliderFloat("Speed", &speed, 0.01f, 1.0f);
}

void Component_WASDInputMove::Save(json& _saveObj)
{
	_saveObj["isActive_"] = isActive_;
	_saveObj["speed_"] = speed;
}

void Component_WASDInputMove::Load(json& _loadObj)
{
	if(_loadObj.contains("isActive_"))isActive_ = _loadObj["isActive_"];
    if(_loadObj.contains("speed_"))speed = _loadObj["speed_"];
}

void Component_WASDInputMove::OnStateChange(std::unordered_map<std::string, State*> _states, State& _nowState)
{
    // ���݂̏�Ԃ��ҋ@��Ԃ�������
    if (_nowState == *_states["idle"]) {
        if (isMove_ == true) {
            _nowState = *_states["move"];
        }
    }
}

void Component_WASDInputMove::Move(XMVECTOR _dir, float _speed)
{
	XMFLOAT3 pos = holder_->GetPosition();
	XMStoreFloat3(&pos, XMLoadFloat3(&pos) + _dir * _speed);
	holder_->SetPosition(pos);
}
