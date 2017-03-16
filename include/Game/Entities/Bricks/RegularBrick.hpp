#pragma once

#include "Brick.hpp"

class RegularBrick : public Brick
{
public:
	RegularBrick(sf::Vector2f pos, int variant = 0);
	void Collided(GameObject* other);
};