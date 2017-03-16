#pragma once

#include "Brick.hpp"

class InvisibleBrick : public Brick
{
public:
	InvisibleBrick(sf::Vector2f pos);
	void Collided(GameObject* other);

	static const char id = 'i';
	static const char frame = 2;
};