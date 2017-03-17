#pragma once

#include "Engine/GameObject.hpp"

class Brick : public GameObject
{
public:
	Brick(sf::Vector2f pos, int variant = 0);
	virtual void Collided(GameObject* other);

	static const sf::Vector2u brickSize;
};