#include "Game/Util/ScoreIO.hpp"

#include "Util/FileIO.hpp"
#include "Util/StringUtil.hpp"

const std::string ScoreIO::scorePath = "data/scores.cfg";

void ScoreIO::LoadScores()
{
	std::string scoreData = FileIO::ReadFile(scorePath);
	if (!scoreData.empty())
	{
		std::vector<std::vector<std::string>> scoreClusters = StringUtil::MakeClusters(StringUtil::Split(scoreData));
		for (const std::vector<std::string>& cluster : scoreClusters)
		{
			std::string levelName = "";
			LevelScoreData levelScoreData;
			bool clusterFailure = false;

			for (size_t i = 0; i < cluster.size(); i++)
			{
				std::string name = "";
				int points = 0;
				bool parsed = ParseScore(cluster[i], name, points);

				if (i == 0)
				{
					if (!parsed)
					{
						clusterFailure = true;
						break;
					}
					else
					{
						levelName = name;
						levelScoreData.points = points;
					}
				}
				else
				{
					if (parsed)
						levelScoreData.stageScores.insert(std::make_pair(name, points));
				}
			}
			if (!clusterFailure)
				levelScores.insert(std::make_pair(levelName, levelScoreData));
		}
	}
}

int ScoreIO::GetLevelScore(const std::string& levelName)
{
	auto levelIt = levelScores.find(levelName);
	if (levelIt != levelScores.end())
		return (*levelIt).second.points;
	return -1;
}

int ScoreIO::GetStageScore(const std::string& levelName, const std::string& stageName)
{
	auto levelIt = levelScores.find(levelName);
	if (levelIt != levelScores.end())
	{
		auto stageIt = (*levelIt).second.stageScores.find(stageName);
		if (stageIt != (*levelIt).second.stageScores.end())
			return (*stageIt).second;
	}
	return -1;
}

bool ScoreIO::ParseScore(const std::string& input, std::string& name, int& score)
{
	size_t lastColon = input.find_last_of(':');
	if (std::string::npos == lastColon)
	{
		LOG_ERROR("Couldn't parse score data");
		return false;
	}

	// Try to cast the part after the final colon into an integer
	try
	{
		score = std::stoi(input.substr(lastColon + 1));
	}
	catch (std::invalid_argument i)
	{
		LOG_ERROR("Couldn't parse score data");
		return false;
	}

	// The part before the colon is the name
	name = input.substr(0, lastColon);
	return true;
}
