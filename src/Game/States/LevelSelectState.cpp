#include "Game/States/LevelSelectState.hpp"

#include "JSON/json.hpp"
using json = nlohmann::json;

#include "Engine/G.hpp"
#include "Game/States/PlayState.hpp"
#include "Util/Tween.hpp"

void LevelSelectState::Init()
{
	std::string levelsData = G::GetAssetManager()->GetLevels();
	if (levelsData == "")
	{
		LOG_ERROR("Trying to load LevelSelect with no data in levels.json");
		return;
	}
	json levelSelectJson = json::parse(levelsData.c_str());

	// Get level datas from JSON
	if (levelSelectJson.find("levels") != levelSelectJson.end())
	{
		json levelsJson = levelSelectJson["levels"];
		if (levelsJson.is_array())
		{
			for (size_t i = 0; i < levelsJson.size(); i++)
			{
				json levelJson = levelsJson[i];
				std::string levelName = "placeholder, pls replace";
				std::string levelFolder = "";
				if (levelJson.find("name") != levelJson.end())
				{
					if (levelJson["name"].is_string())
					{
						levelName = levelJson["name"].get<std::string>();
					}
					else
					{
						LOG_WARNING("\"name\" should be a string");
					}
				}
				else
				{
					LOG_WARNING("No \"name\" found in levels[" + std::to_string(i) + "]");
				}
				if (levelJson.find("folder") != levelJson.end())
				{
					if (levelJson["folder"].is_string())
					{
						levelFolder = levelJson["folder"].get<std::string>();
					}
					else
					{
						LOG_ERROR("\"folder\" should be a string");
						continue;
					}
				}
				else
				{
					LOG_ERROR("No \"folder\" found in levels[" + std::to_string(i) + "]");
					continue;
				}
				levelDatas.insert(std::make_pair(levelName, levelFolder));
			}
		}
		else
		{
			LOG_ERROR("\"levels\" should be an array");
			return;
		}
	}
	else
	{
		LOG_ERROR("No \"levels\" found");
		return;
	}

	// Create buttons according to level datas
	using namespace std::placeholders;
	sf::Vector2u stageSize = GetGame()->GetSize();
	int i = 0;
	for (auto it = levelDatas.begin(); it != levelDatas.end(); it++)
	{
		sf::Vector2f buttonPos = sf::Vector2f(-(float)stageSize.x / 2.0f, i * 66.0f + 30.0f);
		sf::Vector2f buttonSize = sf::Vector2f((float)stageSize.x, 60.0f);
		Button* levelButton = new Button(buttonPos, buttonSize, (ButtonStringCallback)std::bind(&LevelSelectState::LevelButtonPressed, this, _1));
		levelButton->LoadButtonGraphic(G::GetAssetManager()->GetTexture("button.png"), sf::Vector2f(18, 18), sf::Vector2f(6, 6));
		levelButton->GetText()->setFont(*G::GetAssetManager()->GetFont("standur.ttf"));
		levelButton->GetText()->setFillColor(sf::Color::Black);
		levelButton->GetText()->setString((*it).first);
		levelButton->GetText()->setCharacterSize(48);
		levelButton->CenterText();
		Add(levelButton);

		Tween::Start(Ease::Type::QuartOut, buttonPos.x, (float)stageSize.x / 2.0f, 0.7f,
			[levelButton](float v) { levelButton->SetPosition(v, levelButton->GetPosition().y); },
			nullptr, i * 0.1f);

		i++;
	}
}

void LevelSelectState::LevelButtonPressed(std::string buttonText)
{
	PlayState* state = new PlayState(levelDatas[buttonText]);
	GetGame()->SwitchState(state);
}
