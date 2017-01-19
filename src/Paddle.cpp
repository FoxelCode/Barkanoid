#include "Paddle.hpp"

Paddle::Paddle(sf::Vector2f pos)
	: sf::RectangleShape(sf::Vector2f(100.0f, 20.0f))
{
	setPosition(pos);
}
