#include "Game/Entities/Bricks/RegularBrick.hpp"

RegularBrick::RegularBrick(sf::Vector2f pos, int variant)
	: Brick(pos, variant)
{
}

void RegularBrick::Collided(GameObject* other)
{
	Brick::Collided(other);
}
