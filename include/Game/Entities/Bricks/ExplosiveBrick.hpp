#pragma once

#include <functional>

#include "Brick.hpp"

class ExplosiveBrick : public Brick
{
public:
	ExplosiveBrick(sf::Vector2f pos, std::function<void(Brick*)> explosionCallback);
	void Collided(GameObject* other);
	void Kill();

	static const char id = 'e';
	static const char frame = 4;

private:
	std::function<void(Brick*)> explosionCallback;
};