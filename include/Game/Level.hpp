#pragma once

#include <vector>

class Level
{
public:
	Level(std::string levelData);

	std::string GetLevelName() { return levelName; }
	std::string GetStageName() { return stageNames[currentStage]; }
	std::string GetNextStage();

private:
	std::string levelName;
	int currentStage;
	std::vector<std::string> stageNames;
};