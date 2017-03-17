#include "Game/Entities/Bricks/ExplosiveBrick.hpp"

ExplosiveBrick::ExplosiveBrick(sf::Vector2f pos, std::function<void(Brick*)> explosionCallback)
	: Brick(pos, frame), explosionCallback(explosionCallback)
{
}

void ExplosiveBrick::Collided(GameObject* other)
{
	if (explosionCallback != nullptr)
		explosionCallback(this);
	Brick::Collided(other);
}

void ExplosiveBrick::Kill()
{
	Brick::Kill();
	if (explosionCallback != nullptr)
		explosionCallback(this);
}
