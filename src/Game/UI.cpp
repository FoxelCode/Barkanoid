#include "Game/UI.hpp"

UI::UI(sf::Vector2u size)
	: size(size), livesSpacing(6.0f), lifeWidth(36.0f)
{
	livesPos = sf::Vector2f(24.0f + lifeWidth, size.y - 20.0f);
}

UI::~UI()
{
	for (auto& life : lives)
	{
		if (life != nullptr)
		{
			delete life;
			life = nullptr;
		}
	}
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
	if (lives.size() > 0)
	{
		for (auto& life : lives)
		{
			if (life != nullptr)
			{
				delete life;
				life = nullptr;
			}
		}
	}
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