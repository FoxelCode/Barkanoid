#pragma once

#include "GameObject.hpp"

class Ball : public GameObject
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