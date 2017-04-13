#include "Game/States/StageEditState.hpp"

#include "Engine/G.hpp"

StageEditState::StageEditState(std::string levelName)
	: State(), levelName(levelName)
{
}

StageEditState::~StageEditState()
{
}

void StageEditState::Init()
{
	sf::Vector2u size = GetGame()->GetSize();

	std::string levelData = G::GetAssetManager()->GetLevel(levelName);
	if (levelData == "")
	{
		LOG_ERROR("Trying to load level with no data");
		return;
	}
	level = new Level(levelData);
	stage = new Stage(sf::Vector2f(16.0f, 104.0f), sf::Vector2f((float)size.x - gameArea->GetWallThickness() * 2.0f, (float)size.y));


	gameArea = new GameArea(sf::Vector2f(0.0f, 64.0f), sf::Vector2f((float)size.x, (float)size.y - 64.0f));
}

void StageEditState::Update(float delta)
{
	State::Update(delta);
}
