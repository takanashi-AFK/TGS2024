#include "Bullet.h"

// �C���N���[�h
#include "../../../Engine/Global.h"
#include "../../../Engine/ImGui/imgui.h"
#include "../../../Engine/ResourceManager/Model.h"
#include "Components/GaugeComponents/Component_HealthGauge.h"
#include "Stage.h"

Bullet::Bullet(GameObject* _parent)
	:StageObject("Bullet", modelFilePath_, _parent), isActive_(false), frame_(), speed_(), direction_()
{
}

void Bullet::Initialize()
{
	// �R���C�_�[��ǉ�
	AddCollider(new SphereCollider(XMFLOAT3(0, 0, 0), 0.5f));

	// ���f���̓ǂݍ���
	modelHandle_ = Model::Load(modelFilePath_);
	assert(modelHandle_ >= 0);
	
	//SetScale(0.2f);

	// effekseer: :Effect�̓ǂݍ���
	EFFEKSEERLIB::gEfk->AddEffect("Sylph10", "Effects/Sylph10.efk");/*������*/

	// effekseer: :Effect�̍Đ����̐ݒ�
	EFFEKSEERLIB::EFKTransform t;/*������*/
	DirectX::XMStoreFloat4x4(&(t.matrix), transform_.GetWorldMatrix());/*������*/
	t.isLoop = false;/*������*/
	t.maxFrame = 180;/*������*/
	t.speed = 1.f;/*������*/


	// effekseer: :Effect�̍Đ�
	mt = EFFEKSEERLIB::gEfk->Play("Sylph10", t);/*������*/

}

void Bullet::Update()
{
	// ���쒆�łȂ���ΏI��
	if (isActive_ == false)return;

	// �ړ�
	Move(direction_, speed_);

	// �����폜
	//if (EFFEKSEERLIB::gEfk->IsEffectPlaying("Sylph10") == false)KillMe();
	AutoDelete(2.f);

	// effekseer: :Effect�̍Đ����̍X�V
	DirectX::XMStoreFloat4x4(&(mt->matrix), this->GetWorldMatrix());/*������*/
	//SetModelHandle(modelHandle_);
}

void Bullet::Draw()
{
	// ���f���̕`��
	Model::SetTransform(modelHandle_, transform_);
	Model::Draw(modelHandle_);
}

void Bullet::OnCollision(GameObject* _target, Collider* _collider)
{
	if (isActive_ == false)return;

	// �^�[�Q�b�g��StageObject�łȂ��ꍇ�͏������s��Ȃ�
	StageObject* target = dynamic_cast<StageObject*>(_target);
	if (!target) return;

	if (target->GetObjectName() == shooter_->GetObjectName())return;
	auto list = target->FindComponent(HealthGauge);

	if (list.empty()) return;
	// �_���[�W����
	for (auto hm : list) {

		((Component_HealthGauge*)hm)->TakeDamage(20);
		this->KillMe();

		if (((Component_HealthGauge*)hm)->IsDead()) {
			((Stage*)FindObject("Stage"))->DeleteStageObject((StageObject*)_target);
		}
	}

}


//
//void Bullet::DrawData()
//{
//	if (ImGui::TreeNode(" modelFilePath_")) {
//
//		ImGui::Text("imageFilePath_:%s", modelFilePath_.c_str());
//		ImGui::SameLine();
//
//		if (ImGui::SmallButton("...")) {
//			//���݂̃J�����g�f�B���N�g�����o���Ă���
//			char defaultCurrentDir[MAX_PATH];
//			GetCurrentDirectory(MAX_PATH, defaultCurrentDir);
//
//			// �ǉ�����I�u�W�F�N�g�̃��f���t�@�C���p�X��ݒ�
//			{
//				// �u�t�@�C�����J���v�_�C�A���O�̐ݒ�p�\���̂�ݒ�
//				OPENFILENAME ofn; {
//					TCHAR szFile[MAX_PATH] = {}; // �t�@�C�������i�[����o�b�t�@
//					ZeroMemory(&ofn, sizeof(ofn)); // �\���̂̏�����
//					ofn.lStructSize = sizeof(ofn); // �\���̂̃T�C�Y
//					ofn.lpstrFile = szFile; // �t�@�C�������i�[����o�b�t�@
//					ofn.lpstrFile[0] = '\0'; // ������
//					ofn.nMaxFile = sizeof(szFile); // �t�@�C�����o�b�t�@�̃T�C�Y
//					ofn.lpstrFilter = TEXT("PNG�t�@�C��(*.fbx)\0*.png\0���ׂẴt�@�C��(*.*)\0*.*\0"); // �t�B���^�[�iFBX�t�@�C���̂ݕ\���j
//					ofn.nFilterIndex = 1; // �����I������t�B���^�[
//					ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST; // �t���O�i�t�@�C�������݂��邱�ƁA�p�X�����݂��邱�Ƃ��m�F�j
//					ofn.lpstrInitialDir = TEXT("."); // �J�����g�f�B���N�g���������I���ʒu�Ƃ��Đݒ�
//				}
//
//				// �t�@�C����I������_�C�A���O�̕\��
//				if (GetOpenFileName(&ofn) == TRUE) {
//					// �t�@�C���p�X���擾
//					modelFilePath_ = ofn.lpstrFile;
//
//					// �J�����g�f�B���N�g������̑��΃p�X���擾
//					modelFilePath_ = FileManager::GetAssetsRelativePath(modelFilePath_);
//
//					// ���������"\\"��"/"�ɒu��
//					FileManager::ReplaceBackslashes(modelFilePath_);
//
//					// �f�B���N�g����߂�
//					SetCurrentDirectory(defaultCurrentDir);
//
//					// ���f����ǂݍ���
//					Model::Load(modelFilePath_);
//				}
//				else {
//					return;
//				}
//			}
//		}
//		ImGui::TreePop();
//	}
//
//
//}

void Bullet::Move(XMVECTOR _dir, float _speed)
{
	// �ړ�
	XMStoreFloat3(&transform_.position_, XMLoadFloat3(&transform_.position_) + (XMVector3Normalize(_dir) * _speed));
}

void Bullet::AutoDelete(float _sec)
{
	// 0�ȉ��Ȃ�I��
	if (_sec <= 0)return;

	// �o�߃t���[�����w��b���𒴂�����폜
	if (frame_ > FPS * _sec) KillMe();
	else frame_++;
}

