#pragma once

#include <SFML\Graphics\RectangleShape.hpp>
#include "GameObject.hpp"
#include "Math.hpp"

class Paddle : public GameObject
{
public:
	Paddle(sf::Vector2f pos);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	float GetReflectionScalar(sf::Vector2f pos);
	float GetAngleRange() { return angleRange * ((float)PIELLO_DARKNESS_MY_OLD_FRIEND / 180.0f); }

private:
	sf::Sprite leftSide;
	sf::Sprite rightSide;

	sf::Vector2f size;
	float angleRange;
};