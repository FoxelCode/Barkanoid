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
			if (cluster.empty())
				continue;

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

void ScoreIO::WriteScores()
{
	std::string scoreData;
	for (auto& levelScore : levelScores)
	{
		// Insert a newline to separate level clusters
		if (!scoreData.empty())
			scoreData += "\n";

		// Add the level's score
		scoreData += levelScore.first + ": " + std::to_string(levelScore.second.points) + "\n";
		for (auto& stageScore : levelScore.second.stageScores)
		{
			// Add all stage scores
			scoreData += stageScore.first + ": " + std::to_string(stageScore.second) + "\n";
		}
	}
	FileIO::WriteFile(scorePath, scoreData);
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

bool ScoreIO::TrySetLevelScore(const std::string& levelName, int score)
{
	// Check if the level already has score data
	auto levelIt = levelScores.find(levelName);
	if (levelIt != levelScores.end())
	{
		// If the new score is larger than the one already stored, set the new highscore
		if (score > (*levelIt).second.points)
		{
			(*levelIt).second.points = score;
			WriteScores();
			return true;
		}
	}
	else
	{
		// If the level doesn't have any recorded score data, create one for it
		LevelScoreData levelData;
		levelData.points = score;
		levelScores.insert(std::make_pair(levelName, levelData));
		WriteScores();
		return true;
	}
	return false;
}

bool ScoreIO::TrySetStageScore(const std::string& levelName, const std::string& stageName, int score)
{
	// Check if the level the stage belongs to already has score data
	auto levelIt = levelScores.find(levelName);
	if (levelIt != levelScores.end())
	{
		// Check if the stage itself already has score data
		auto stageIt = (*levelIt).second.stageScores.find(stageName);
		if (stageIt != (*levelIt).second.stageScores.end())
		{
			// If the new score is larger than the one already stored, set the new highscore
			if (score > (*stageIt).second)
			{
				(*stageIt).second = score;
				WriteScores();
				return true;
			}
		}
		else
		{
			// If the stage has no score data, create one for it
			(*levelIt).second.stageScores.insert(std::make_pair(stageName, score));
			WriteScores();
			return true;
		}
	}
	else
	{
		// If the level the stage belongs to has no score data, create one for it
		// and set the new highscore for the stage
		LevelScoreData levelData;
		levelData.points = -1;
		levelData.stageScores.insert(std::make_pair(stageName, score));
		levelScores.insert(std::make_pair(levelName, levelData));
		WriteScores();
		return true;
	}
	return false;
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
