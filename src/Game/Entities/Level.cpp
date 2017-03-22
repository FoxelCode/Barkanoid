#include "Game/Entities/Level.hpp"

#include "JSON/json.hpp"
using json = nlohmann::json;

#include "Util/StringUtil.hpp"

Level::Level(std::string levelData)
	: currentStage(-1)
{
	if (levelData == "")
	{
		LOG_ERROR("Trying to load Level with no data");
		return;
	}
	
	// Separate level data into lines
	std::vector<std::string> dataLines = StringUtil::Split(levelData);

	// First line is the level name
	levelName = dataLines[0];

	// The rest of the lines (until the first empty line) are stage names
	for (size_t i = 1; i < dataLines.size(); i++)
	{
		if (StringUtil::IsWhitespace(dataLines[i]))
			break;
		stageNames.push_back(dataLines[i]);
	}
}

std::string Level::GetNextStage()
{
	if (currentStage < ((int)stageNames.size() - 1))
	{
		currentStage++;
		return stageNames[currentStage];
	}
	return "";
}
