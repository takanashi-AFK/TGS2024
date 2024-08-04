#pragma once
class ScoreManager
{
private:
	int score_;

public:
	ScoreManager();

	void AddScore(int _gameScore);



	int SetScore(int _score) {
		score_ = _score;
	}

	int  GetScore() {
		return score_;
	}

};

