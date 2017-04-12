#include "Game/Barkanoid.hpp"

#include "Engine/G.hpp"

Barkanoid::Barkanoid(sf::RenderWindow& window, sf::Vector2u size, State* initialState, const float delta)
	: Game(window, size, initialState, delta)
{
	// Load the high scores and also write them back, cleaning the score file up
	scoreIO.LoadScores();
	scoreIO.WriteScores();

	audio.SetMute(true);
}
