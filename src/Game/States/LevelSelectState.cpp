#include "Game/States/LevelSelectState.hpp"

#include "JSON/json.hpp"
using json = nlohmann::json;

#include "Engine/G.hpp"
#include "Game/States/PlayState.hpp"
#include "Util/Tween.hpp"
#include "Util/StringUtil.hpp"
#include "UI/VerticalScrollArea.hpp"

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

		levelDatas.insert(std::make_pair(levelName, levelFile));
	}

	sf::Vector2u stageSize = GetGame()->GetSize();

	// Create scroll area for level buttons
	VerticalScrollArea* scrollArea = new VerticalScrollArea(sf::Vector2f(), sf::Vector2f(stageSize));
	Add(scrollArea);

	// Create buttons according to level datas
	int i = 0;
	for (auto it = levelDatas.begin(); it != levelDatas.end(); it++)
	{
		sf::Vector2f buttonPos = sf::Vector2f(-(float)stageSize.x, 0.0f);
		sf::Vector2f buttonSize = sf::Vector2f((float)stageSize.x, buttonHeight);
		Button* levelButton = new Button(buttonPos, buttonSize, (ButtonStringCallback)std::bind(&LevelSelectState::LevelButtonPressed, this, std::placeholders::_1),
			Alignment(HorizontalAlign::Left, VerticalAlign::Top));
		levelButton->LoadButtonGraphic(G::GetAssetManager()->GetTexture("button.png"), sf::Vector2f(18, 18), sf::Vector2f(6, 6));
		levelButton->GetText()->setFont(*G::GetAssetManager()->GetFont("OneTrickPony.otf"));
		levelButton->GetText()->setFillColor(sf::Color::Black);
		levelButton->GetText()->setString((*it).first);
		levelButton->GetText()->setCharacterSize(40);
		levelButton->UpdateLayout();
		Add(levelButton);
		scrollArea->AddChild(levelButton);
		// Fix the X position of the button since adding it to the scroll area changes its position
		levelButton->SetPosition(buttonPos.x, levelButton->GetPosition().y);

		Tween::Start(Ease::Type::QuartOut, buttonPos.x, 0.0f, 0.7f,
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
