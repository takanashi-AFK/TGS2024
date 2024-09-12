#pragma once

#include <vector>
#include <string>

using namespace std;

class RankingManager
{
private:
    std::vector<int> scores_;  // スコアのみを保存

public:
    /// <summary> シングルトンインスタンスを取得 </summary>
    static RankingManager& GetInstance();
    
    /// <summary> 読込（CSV形式） </summary>
    bool Load(string _filePath);

    /// <summary> 保存（CSV形式） </summary>
    bool Save(string _filePath);

    /// <summary> スコアを追加 </summary>
    void AddScore(int _score) { scores_.push_back(_score); }

    /// <summary> スコアをソート </summary>
    void SortScores();

/*
getter :*/
    /// <summary> 指定したランクのスコアを取得 </summary>
    int GetScore(int _rank) const;

    /// <summary> スコアの数を取得 </summary>
    vector<int> GetAllScores() const { return scores_; }

private:
    // コンストラクタはプライベート
    RankingManager() {}

    // コピーコンストラクタ・代入演算子を削除
    RankingManager(const RankingManager&) = delete;
    RankingManager& operator=(const RankingManager&) = delete;

};