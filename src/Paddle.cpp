#include "Paddle.hpp"

Paddle::Paddle(sf::Vector2f pos)
	: sf::RectangleShape(sf::Vector2f(100.0f, 16.0f)), angleRange(160.0f)
{
	setPosition(pos);
}

float Paddle::GetReflectionScalar(sf::Vector2f pos)
{
	return fmaxf(fminf((pos.x - (getPosition().x + getGlobalBounds().width / 2.0f)) / getGlobalBounds().width, 1.0f), -1.0f);
}
