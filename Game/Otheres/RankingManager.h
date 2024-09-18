#pragma once

#include <vector>
#include <string>
#include <utility>

using namespace std;

class RankingManager
{
private:
    // ユーザー名とスコアのペアを保存する
    std::vector<std::pair<std::string, int>> scores_;

public:
    /// <summary> シングルトンインスタンスを取得 </summary>
    static RankingManager& GetInstance();

    /// <summary> 読込（CSV形式） </summary>
    bool Load(string _filePath);

    /// <summary> 保存（CSV形式） </summary>
    bool Save(string _filePath);

    /// <summary> スコアを追加 </summary>
    void AddScore(const std::string& _userName, int _score);

    /// <summary> スコアをソート </summary>
    void SortScores();

/*
getter :*/
    /// <summary> 指定したランクのスコアを取得 </summary>
    int GetScore(int _rank) const;

    /// <summary> 指定したランクのユーザー名を取得 </summary>
    std::string GetUser(int _rank) const;

    /// <summary> 全てのスコアとユーザー名を取得 </summary>
    std::vector<std::pair<std::string, int>> GetAllScores() const { return scores_; }

private:
    // コンストラクタはプライベート
    RankingManager() {}

    // コピーコンストラクタ・代入演算子を削除
    RankingManager(const RankingManager&) = delete;
    RankingManager& operator=(const RankingManager&) = delete;
};
