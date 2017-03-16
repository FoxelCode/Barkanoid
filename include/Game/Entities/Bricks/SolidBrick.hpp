#pragma once

#include "Brick.hpp"

class SolidBrick : public Brick
{
public:
	SolidBrick(sf::Vector2f pos);
	void Collided(GameObject* other);

	static const char id = 's';
	static const char frame = 3;
};