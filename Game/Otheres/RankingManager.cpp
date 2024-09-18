#include "RankingManager.h"
#include "../../Engine/Json/JsonReader.h"
using namespace std;

RankingManager& RankingManager::GetInstance()
{
    static RankingManager instance;
    return instance;
}

bool RankingManager::Load(string _filePath)
{
    // jsonオブジェクトを作成
    json loadData;

    // ファイル読込
    if (!JsonReader::Load(_filePath, loadData)) return false;

    // スコア配列をクリアして再構築
    scores_.clear();

    // jsonの中身を取得
    for (auto& obj : loadData) {
        // jsonの中身がuserNameとscoreを持っているか確認
		if(obj.contains("userName") && obj.contains("score"))
		scores_.push_back(make_pair(obj["userName"],obj["score"]));
	}

    // スコアをソート
    SortScores();

    // スコアが存在するかどうかを返す
    return !scores_.empty();
}

bool RankingManager::Save(string _filePath)
{
    // jsonオブジェクトを作成
    json saveData;

    // スコアをソート
    SortScores();

    // スコアをjsonに格納
    for (const auto& entry : scores_)
    {
		saveData.push_back({ {"userName", entry.first}, {"score", entry.second} });
	}

    // ファイルを閉じる
    return (JsonReader::Save(_filePath, saveData));
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
