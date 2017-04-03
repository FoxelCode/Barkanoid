#pragma once

#include <map>

class ScoreIO
{
public:
	ScoreIO() {}

	void LoadScores();
	void WriteScores();

	int GetLevelScore(const std::string& levelName);
	int GetStageScore(const std::string& levelName, const std::string& stageName);

	bool TrySetLevelScore(const std::string& levelName, int score);
	bool TrySetStageScore(const std::string& levelName, const std::string& stageName, int score);

private:
	static const std::string scorePath;

	bool ParseScore(const std::string& input, std::string& name, int& score);

	struct LevelScoreData
	{
		int points;
		std::map<std::string, int> stageScores;
	};
	std::map<std::string, LevelScoreData> levelScores;
};