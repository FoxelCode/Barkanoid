#pragma once

#include <SFML\Graphics\CircleShape.hpp>
#include "Updatable.hpp"

class Ball : public sf::CircleShape, Updatable
{
public:
	Ball(sf::Vector2f pos);

	void Update(float delta);
	void Separate(sf::Vector2f separation);

private:
	float radius;
	sf::Vector2f velocity;
};