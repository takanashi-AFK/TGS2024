#include "ScoreManager.h"

ScoreManager::ScoreManager()
{
	score_ = 0;
}
void ScoreManager::AddScore(int _gameScore)
{
	score_ += _gameScore;
}

