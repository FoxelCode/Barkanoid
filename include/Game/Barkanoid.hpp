#pragma once

#include "Engine/Game.hpp"
#include "Game/Util/ScoreIO.hpp"

class Barkanoid : public Game
{
public:
	Barkanoid(sf::RenderWindow& window, sf::Vector2u size, State* initialState, const float delta);

	ScoreIO& GetScoreIO() { return scoreIO; }

private:
	ScoreIO scoreIO;
};