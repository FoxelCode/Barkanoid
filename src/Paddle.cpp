#include "Paddle.hpp"

Paddle::Paddle(sf::Vector2f pos)
	: sf::RectangleShape(sf::Vector2f(100.0f, 20.0f)), angleRange(180.0f)
{
	setPosition(pos);
}

float Paddle::GetReflectionScalar(sf::Vector2f pos)
{
	return fmaxf(fminf(((getPosition().x + getGlobalBounds().width / 2.0f) - pos.x) / getGlobalBounds().width, 1.0f), -1.0f);
}
