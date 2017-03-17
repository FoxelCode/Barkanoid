#include "Game/States/LevelSelectState.hpp"

#include "JSON/json.hpp"
using json = nlohmann::json;

#include "Engine/G.hpp"
#include "Game/States/PlayState.hpp"
#include "Util/Tween.hpp"

void LevelSelectState::Init()
{
	// Get level folders
	std::vector<std::string> levelFolders = G::GetAssetManager()->GetLevels();

	// Get visual names for all levels
	for each (std::string levelFolder in levelFolders)
	{
		std::string levelJsonStr = G::GetAssetManager()->GetLevel(levelFolder);
		if (levelJsonStr == "")
		{
			LOG_WARNING("No level data found");
			continue;
		}

		json levelJson = json::parse(levelJsonStr.c_str());

		std::string levelVisualName = levelFolder;
		if (levelJson.find("name") != levelJson.end())
		{
			if (levelJson["name"].is_string())
				levelVisualName = levelJson["name"].get<std::string>();
			else
				LOG_WARNING("\"name\" should be a string, assuming " + levelFolder);
		}
		else
			LOG_WARNING("No \"name\" found, assuming " + levelFolder);

		levelDatas.insert(std::make_pair(levelVisualName, levelFolder));
	}

	// Create buttons according to level datas
	sf::Vector2u stageSize = GetGame()->GetSize();
	int i = 0;
	for (auto it = levelDatas.begin(); it != levelDatas.end(); it++)
	{
		sf::Vector2f buttonPos = sf::Vector2f(-(float)stageSize.x / 2.0f, i * 66.0f);
		sf::Vector2f buttonSize = sf::Vector2f((float)stageSize.x, 60.0f);
		Button* levelButton = new Button(buttonPos, buttonSize, (ButtonStringCallback)std::bind(&LevelSelectState::LevelButtonPressed, this, std::placeholders::_1),
			Alignment(HorizontalAlign::Middle, VerticalAlign::Top));
		levelButton->LoadButtonGraphic(G::GetAssetManager()->GetTexture("button.png"), sf::Vector2f(18, 18), sf::Vector2f(6, 6));
		levelButton->GetText()->setFont(*G::GetAssetManager()->GetFont("OneTrickPony.otf"));
		levelButton->GetText()->setFillColor(sf::Color::Black);
		levelButton->GetText()->setString((*it).first);
		levelButton->GetText()->setCharacterSize(40);
		levelButton->CenterText();
		Add(levelButton);

		Tween::Start(Ease::Type::QuartOut, buttonPos.x, (float)stageSize.x / 2.0f, 0.7f,
			[levelButton](float v) { levelButton->SetPosition(v, levelButton->GetPosition().y); },
			nullptr, Tween::OneShot, i * 0.1f);

		i++;
	}
}

void LevelSelectState::LevelButtonPressed(std::string buttonText)
{
	PlayState* state = new PlayState(levelDatas[buttonText]);
	GetGame()->SwitchState(state);
}
