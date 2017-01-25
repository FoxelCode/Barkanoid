#pragma once

#include <SFML\Graphics\RectangleShape.hpp>
#include "Math.hpp"

class Paddle : public sf::RectangleShape
{
public:
	Paddle(sf::Vector2f pos);

	float GetReflectionScalar(sf::Vector2f pos);
	float GetAngleRange() { return angleRange * (PIELLO_DARKNESS_MY_OLD_FRIEND / 180.0f); }

private:
	float angleRange;
};