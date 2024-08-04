#pragma once
#include "DirectX/Direct3D.h"

// ���� �}�N�� �������������������������������������� //

//���S�Ƀ��������J�����邽�߂̃}�N��
#define SAFE_DELETE(p) {if ((p)!=nullptr) { delete (p); (p)=nullptr;}}
#define SAFE_DELETE_ARRAY(p) {if ((p)!=nullptr) { delete[] (p); (p)=nullptr;}}
#define SAFE_RELEASE(p) {if ((p)!=nullptr) { p->Release(); (p)=nullptr;}}

// XMFLOAT3�^�̕ϐ����R���}��؂�ŕ\������}�N��
#define REFERENCE_XMFLOAT3(p) p.x,p.y,p.z 
#define REFERENCE_XMFLOAT4(p) p.x,p.y,p.z,p.w 
#define REFERENCE_XMVECTOR3(p) XMVectorGetX(p),XMVectorGetY(p),XMVectorGetZ(p)

// ���� �萔 ���������������������������������������� //

const float FPS = 60.0f;	// �t���[�����[�g

// �������������������������������������������������� //

// �t�@�C���Ǘ�namespace
namespace FileManager {
	// ��������̑S�Ă� "\\" �� "/" �ɒu������֐�
	void ReplaceBackslashes(string& str);

	// �J�����g�f�B���N�g������̑��΃p�X���擾����֐�
	std::string GetAssetsRelativePath(const std::string& absolutePath);
}

XMFLOAT3 operator+(XMFLOAT3& a, const XMFLOAT3& b);


/// �Վ��̃O���[�o���ϐ� fix: �{���͂����ɒu���ׂ��ł͂Ȃ� 
/// �X�R�A�}�l�[�W���[���쐬���邱�Ƃŉ�������

// �Q�[���̃X�R�A
//extern int g_score;