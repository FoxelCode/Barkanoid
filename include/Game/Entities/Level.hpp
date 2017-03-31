#pragma once

#include <vector>

class Level
{
public:
	Level(std::string levelData);

	void Reset() { currentStage = -1; }

	std::string GetLevelName() { return levelName; }
	std::string GetStageName();
	std::string GetNextStage();

private:
	std::string levelName;
	int currentStage;
	std::vector<std::string> stageNames;
};