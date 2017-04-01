#pragma once

#include <vector>

class Level
{
public:
	Level(std::string levelData);

	void Reset() { currentStage = -1; }

	std::string GetLevelName() const { return levelName; }
	std::string GetStageName();
	std::string GetNextStage();
	const std::vector<std::string> GetStageNames() const { return stageNames; }

private:
	std::string levelName;
	int currentStage;
	std::vector<std::string> stageNames;
};