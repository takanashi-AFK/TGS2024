#include "RankingManager.h"

#include "../../../Engine/ResourceManager/CsvReader.h"

#include <filesystem>
#include <fstream>
namespace fs = std::filesystem;

RankingManager& RankingManager::GetInstance()
{
    static RankingManager instance;
    return instance;
}

bool RankingManager::Load(string _filePath)
{
    // csvリーダーを作成
    CsvReader csvReader;

    // ファイル読み込み
    if (!csvReader.Load(_filePath)) return false;

    // スコア配列をクリアして再構築
    scores_.clear();
    for (int y = 0; y < csvReader.GetHeight(); y++)scores_.push_back(csvReader.GetValue(0, y));

    // スコアが存在するかどうかを返す
    return scores_.empty() == false;
}

bool RankingManager::Save(string _filePath)
{
    // ファイルを開く
    ofstream ofs(_filePath);
    if(!ofs.is_open())return false;

    // スコアをソート
    SortScores();

    // スコアを書き込む
    for(int score : scores_)ofs << score << endl;

    // ファイルを閉じる
    ofs.close();
    return true;
}

void RankingManager::SortScores()
{
    // スコアを降順にソート
	sort(scores_.begin(), scores_.end(), greater<int>());
}

int RankingManager::GetScore(int _rank) const
{
    // ランクが範囲外の場合は0を返す
    if(_rank < 0 || _rank >= scores_.size())return 0;
	
    // ランクに対応するスコアを返す
    return scores_[_rank];
}