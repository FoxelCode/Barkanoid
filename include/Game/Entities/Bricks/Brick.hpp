#pragma once

#include "Engine/GameObject.hpp"

class Brick : public GameObject
{
public:
	Brick(sf::Vector2f pos, int variant = 0);
	virtual void Collided(GameObject* other);

	virtual void Kill();

	static const sf::Vector2u brickSize;
};