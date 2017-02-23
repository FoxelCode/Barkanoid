#include "Game/UI.hpp"

UI::UI(sf::Vector2u size)
	: size(size), livesSpacing(6.0f), lifeWidth(40.0f)
{
	livesPos = sf::Vector2f(40.0f, size.y - 20.0f);
}

UI::~UI()
{
	lives.clear();
}

void UI::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for each (Paddle* paddle in lives)
	{
		target.draw(*paddle, states);
	}
}

void UI::SetLives(size_t amount)
{
	lives.clear();
	for (size_t i = 0; i < amount; i++)
	{
		sf::Vector2f lifePos = livesPos + sf::Vector2f(i * (lifeWidth + livesSpacing), 0.0f);
		Paddle* life = new Paddle(lifePos);
		life->SetActive(false);
		life->SetWidth(lifeWidth);
		lives.push_back(life);
	}
}
