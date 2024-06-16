#include "Global.h"

void FileManager::ReplaceBackslashes(string& str)
{
	size_t found = str.find("\\");
	while (found != string::npos) {
		str.replace(found, 1, "/"); // "\\" を "/" に置換する
		found = str.find("\\", found + 1); // 次の "\\" を検索する
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