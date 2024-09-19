#pragma once
#include "DirectX/Direct3D.h"
#include <filesystem>
#include <string>

// ���� �}�N�� �������������������������������������� //

//���S�Ƀ��������J�����邽�߂̃}�N��
#define SAFE_DELETE(p) {if ((p)!=nullptr) { delete (p); (p)=nullptr;}}
#define SAFE_DELETE_ARRAY(p) {if ((p)!=nullptr) { delete[] (p); (p)=nullptr;}}
#define SAFE_RELEASE(p) {if ((p)!=nullptr) { p->Release(); (p)=nullptr;}}

// XMFLOAT3�^�̕ϐ����R���}��؂�ŕ\������}�N��
#define REFERENCE_XMFLOAT3(p) p.x,p.y,p.z 
#define REFERENCE_XMFLOAT4(p) p.x,p.y,p.z,p.w 
#define REFERENCE_XMVECTOR3(p) XMVectorGetX(p),XMVectorGetY(p),XMVectorGetZ(p)
#define REFERENCE_XMINT2(p) p.x,p.y

// �I�y���[�^�[�̃I�[�o�[���[�h
XMFLOAT3 operator+(XMFLOAT3& a, const XMFLOAT3& b);
XMFLOAT3 operator-(XMFLOAT3& a, const XMFLOAT3& b);
bool operator == (XMFLOAT3& a, const XMFLOAT3& b);
// ���� �萔 ���������������������������������������� //

const float FPS = 60.0f;	// �t���[�����[�g

// �������������������������������������������������� //

namespace ScoreManager {
/*
valeable :*/
	extern int time;		// �^�C��
	extern int playerHp;	// �v���C���[��HP
	extern bool isClear;	// �N���A�������ǂ���
}

// �t�@�C���Ǘ�namespace
namespace FileManager {
	// ��������̑S�Ă� "\\" �� "/" �ɒu������֐�
	void ReplaceBackslashes(string& str);

	// �J�����g�f�B���N�g������̑��΃p�X���擾����֐�
	std::string GetAssetsRelativePath(const std::string& absolutePath);

	// �֐�: �p�X����t�@�C�������擾����
	std::string GetFileNameFromPath(const std::string& path);

	// �֐�: �p�X����g���q�Ȃ��̃t�@�C�������擾����
	std::string GetFileNameWithoutExtension(const std::string& path);
}

namespace Controller {
extern bool g_isConnectController;	// �R���g���[���[���ڑ�����Ă��邩�ǂ���
bool IsControllerConnected(int controllerIndex);

}

/// �Վ��̃O���[�o���ϐ� fix: �{���͂����ɒu���ׂ��ł͂Ȃ� 
extern string g_selectedStage;	// �I�����ꂽ�X�e�[�W

// �G�t�F�N�g�f�[�^
// fix: �{���͂����ɒu���ׂ��ł͂Ȃ�
struct EffectData {
	std::string name;
	std::string path;
	XMFLOAT3 scale;
};
