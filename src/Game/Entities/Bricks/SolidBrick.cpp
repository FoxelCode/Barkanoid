#include "Game/Entities/Bricks/SolidBrick.hpp"

SolidBrick::SolidBrick(sf::Vector2f pos)
	: Brick(pos, frame)
{
}

void SolidBrick::Collided(GameObject* other)
{
}
