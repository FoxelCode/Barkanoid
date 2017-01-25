#pragma once

#include <SFML\Graphics\CircleShape.hpp>

#include "IUpdatable.hpp"
class Ball : public sf::CircleShape, IUpdatable
{
public:
	Ball(sf::Vector2f pos);

	void Update(float delta);
	void Separate(sf::Vector2f separation);
	void TurnTowards(float angle);

private:
	float radius;
	sf::Vector2f velocity;
};