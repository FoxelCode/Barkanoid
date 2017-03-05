#include "Game/Entities/UI.hpp"

#include "Engine/G.hpp"

UI::UI(sf::Vector2u size)
	: size(size), livesSpacing(6.0f), lifeWidth(36.0f)
{
	livesPos = sf::Vector2f(24.0f + lifeWidth, size.y - 20.0f);

	timer.setPosition(size.x - 100.0f, 8.0f);
	timer.setFont(*G::GetAssetManager()->GetFont("standur.ttf"));
	timer.setFillColor(sf::Color::White);
	timer.setString("0:00");

	points.setPosition(8.0f, 8.0f);
	points.setFont(*G::GetAssetManager()->GetFont("standur.ttf"));
	points.setFillColor(sf::Color::White);
	points.setString("0");
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
	target.draw(timer, states);
	target.draw(points, states);
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

void UI::SetTime(sf::Time time)
{
	int totalSeconds = (int)time.asSeconds();
	int minutes = totalSeconds / 60;
	int seconds = totalSeconds - minutes * 60;
	std::string secondsStr = (seconds < 10) ? ("0" + std::to_string(seconds)) : std::to_string(seconds);
	timer.setString(std::to_string(minutes) + ":" + secondsStr);
}

void UI::SetPoints(int points)
{
	this->points.setString(std::to_string(points));
}
