#include "RankingManager.h"
#include "../../../Engine/ResourceManager/CsvReader.h"

#include <filesystem>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;
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
    for (int y = 0; y < csvReader.GetHeight(); y++)
    {
        // csvの1列目にユーザー名、2列目にスコアがあると仮定
        string userName = csvReader.GetString(1, y);
        int score = csvReader.GetValue(2, y);
        scores_.push_back(make_pair(userName, score));
    }

    // スコアが存在するかどうかを返す
    return !scores_.empty();
}

bool RankingManager::Save(string _filePath)
{
    // ファイルを開く
    ofstream ofs(_filePath);
    if (!ofs.is_open()) return false;

    // スコアをソート
    SortScores();

    // スコアを書き込む
    for (const auto& entry : scores_)
    {
        ofs << entry.first << "," << entry.second << endl; // ユーザー名,スコアを保存
    }

    // ファイルを閉じる
    ofs.close();
    return true;
}

void RankingManager::AddScore(const std::string& _userName, int _score)
{
	// スコアを追加
	scores_.push_back(make_pair(_userName, _score));
}

void RankingManager::SortScores()
{
    // スコアを降順にソート
    sort(scores_.begin(), scores_.end(), [](const pair<string, int>& a, const pair<string, int>& b) {
        return a.second > b.second;
        });
}

int RankingManager::GetScore(int _rank) const
{
    // ランクが範囲外の場合は0を返す
    if (_rank < 0 || _rank >= scores_.size()) return 0;

    // ランクに対応するスコアを返す
    return scores_[_rank].second;
}

string RankingManager::GetUser(int _rank) const
{
    // ランクが範囲外の場合は空文字を返す
    if (_rank < 0 || _rank >= scores_.size()) return "";

    // ランクに対応するユーザー名を返す
    return scores_[_rank].first;
}
