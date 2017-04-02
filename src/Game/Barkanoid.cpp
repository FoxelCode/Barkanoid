#include "Game/Barkanoid.hpp"

#include "Engine/G.hpp"

Barkanoid::Barkanoid(sf::RenderWindow& window, sf::Vector2u size, State* initialState, const float delta)
	: Game(window, size, initialState, delta)
{
	scoreIO.LoadScores();
}
