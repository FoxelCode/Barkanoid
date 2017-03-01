#include "Game/Level.hpp"

#include "JSON/json.hpp"
using json = nlohmann::json;

Level::Level(std::string levelData)
	: currentStage(-1)
{
	if (levelData == "")
	{
		LOG_ERROR("Trying to load Level with no data");
		return;
	}
	json levelJson = json::parse(levelData.c_str());

	if (levelJson.find("stages") != levelJson.end())
	{
		json stagesJson = levelJson["stages"];
		if (stagesJson.is_array())
		{
			for (size_t i = 0; i < stagesJson.size(); i++)
			{
				if (!stagesJson[i].is_string())
				{
					LOG_ERROR("stages[" + std::to_string(i) + "] should be a string");
					continue;
				}
				stageNames.push_back(stagesJson[i].get<std::string>());
			}
		}
		else
		{
			LOG_ERROR("\"stages\" should be an array");
			return;
		}
	}
	else
	{
		LOG_ERROR("No \"stages\" found");
		return;
	}
}

std::string Level::GetNextStage()
{
	if (currentStage < ((int)stageNames.size() - 1))
	{
		currentStage++;
		return stageNames[currentStage];
	}
	LOG_ERROR("Trying to get next Stage but Level has no Stages left");
	return "";
}
