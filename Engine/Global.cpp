#include "Global.h"

void FileManager::ReplaceBackslashes(string& _str)
{
	size_t found = _str.find("\\");
	while (found != string::npos) {
		_str.replace(found, 1, "/"); // "\\" を "/" に置換する
		found = _str.find("\\", found + 1); // 次の "\\" を検索する
	}
}

std::string FileManager::GetAssetsRelativePath(const std::string& absolutePath)
{
	const std::string assetsFolder = "Assets\\";
	// "Assets\\" の位置を検索
	size_t assetsPos = absolutePath.find(assetsFolder);
	if (assetsPos != std::string::npos) {
		// "Assets\\" の部分を除いた、それ以降の部分を取得
		std::string relativePath = absolutePath.substr(assetsPos + assetsFolder.size());
		return relativePath;
	}
	else {
		// "Assets\\" が見つからない場合は、元のファイルパスを返す
		return absolutePath;
	}
}

XMFLOAT3 operator+(XMFLOAT3& a, const XMFLOAT3& b)
{
	return XMFLOAT3(a.x + b.x, a.y + b.y, a.z + b.z);
}

// ゲームのスコア
int g_score = 0;

string stringConverter::ConvertToLower(string _str)
{
	for (int i = 0; i < _str.size(); i++) {
		_str[i] = tolower(_str[i]);
	}
	return _str;
}

string stringConverter::ConvertToUpper(string _str)
{
	for (int i = 0; i < _str.size(); i++) {
		_str[i] = toupper(_str[i]);
	}
	return _str;
}
