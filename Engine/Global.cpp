#include "Global.h"

void FileManager::ReplaceBackslashes(string& str)
{
	size_t found = str.find("\\");
	while (found != string::npos) {
		str.replace(found, 1, "/"); // "\\" �� "/" �ɒu������
		found = str.find("\\", found + 1); // ���� "\\" ����������
	}
}

std::string FileManager::GetAssetsRelativePath(const std::string& absolutePath)
{
	const std::string assetsFolder = "Assets\\";
	// "Assets\\" �̈ʒu������
	size_t assetsPos = absolutePath.find(assetsFolder);
	if (assetsPos != std::string::npos) {
		// "Assets\\" �̕������������A����ȍ~�̕������擾
		std::string relativePath = absolutePath.substr(assetsPos + assetsFolder.size());
		return relativePath;
	}
	else {
		// "Assets\\" ��������Ȃ��ꍇ�́A���̃t�@�C���p�X��Ԃ�
		return absolutePath;
	}
}

std::string FileManager::GetFileNameFromPath(const std::string& path)
{
	return std::filesystem::path(path).filename().string();
}


// �֐�: �p�X����g���q�Ȃ��̃t�@�C�������擾����
std::string FileManager::GetFileNameWithoutExtension(const std::string& path) {
	return std::filesystem::path(path).stem().string();
}
XMFLOAT3 operator+(XMFLOAT3& a, const XMFLOAT3& b)
{
	return XMFLOAT3(a.x + b.x, a.y + b.y, a.z + b.z);
}

XMFLOAT3 operator-(XMFLOAT3& a, const XMFLOAT3& b)
{
	return XMFLOAT3(a.x - b.x, a.y - b.y, a.z - b.z);
}

bool operator == (XMFLOAT3& a, const XMFLOAT3& b)
{
	return (a.x == b.x) && (a.y == b.y) && (a.z == b.z);
}

// �Q�[���̃X�R�A
namespace ScoreManager {
	float g_Score = 0.f;

	void ScoreManager::AddScore(int score) {
		g_Score += score; 
	}

	int ScoreManager::GetScore(){
		return g_Score; 
	}
}
