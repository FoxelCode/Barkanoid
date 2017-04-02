#include "Game/States/LevelSelectState.hpp"

#include "JSON/json.hpp"
using json = nlohmann::json;

#include "Engine/G.hpp"
#include "Game/States/PlayState.hpp"
#include "Util/Tween.hpp"
#include "Util/StringUtil.hpp"
#include "UI/VerticalScrollArea.hpp"
#include "Game/UI/LevelEntry.hpp"

const float LevelSelectState::buttonHeight = 60.0f;
const float LevelSelectState::buttonSpacing = 6.0f;
const float LevelSelectState::editButtonWidth = 40.0f;

void LevelSelectState::Init()
{
	// Get level files
	std::vector<std::string> levelFiles = G::GetAssetManager()->GetLevels();

	// Get visual names for all levels
	for each (std::string levelFile in levelFiles)
	{
		std::string levelName = "mmm yes this is good name";
		std::string levelString = G::GetAssetManager()->GetLevel(levelFile);
		if (levelString == "")
		{
			LOG_WARNING("No level data found");
			continue;
		}
		levelName = StringUtil::Split(levelString)[0];

		levelDatas.push_back(std::make_pair(levelName, levelFile));
	}

	sf::Vector2u stageSize = GetGame()->GetSize();

	// Create scroll area for level buttons
	VerticalScrollArea* scrollArea = new VerticalScrollArea(sf::Vector2f(), sf::Vector2f(stageSize));
	Add(scrollArea);

	// Create buttons according to level datas
	int i = 0;
	for (auto it = levelDatas.begin(); it != levelDatas.end(); it++)
	{
		Level level = Level(G::GetAssetManager()->GetLevel((*it).second));

		LevelEntry* levelEntry = new LevelEntry(level, (ButtonStringCallback)std::bind(&LevelSelectState::LevelButtonPressed, this, std::placeholders::_1), sf::Vector2f(), sf::Vector2f((float)stageSize.x, 0.0f));
		Add(levelEntry);
		scrollArea->AddChild(levelEntry);
		levelEntry->SetPosition(sf::Vector2f(-(float)stageSize.x, levelEntry->GetPosition().y));

		Tween::Start(Ease::Type::QuartOut, levelEntry->GetPosition().x, 0.0f, 0.7f,
			[levelEntry](float v) { levelEntry->SetPosition(sf::Vector2f(v, levelEntry->GetPosition().y)); },
			nullptr, Tween::OneShot, i * 0.1f);

		i++;
	}
}

void LevelSelectState::LevelButtonPressed(std::string buttonText)
{
	PlayState* state = nullptr;
	for (const auto& levelData : levelDatas)
	{
		if (levelData.first == buttonText)
			state = new PlayState(levelData.second);
	}
	if (state == nullptr)
	{
		LOG_ERROR("Couldn't find the levelData for \"" + buttonText + "\", how'd this even happen?");
		return;
	}
	GetGame()->SwitchState(state);
}
