#include "Game/Entities/Bricks/InvisibleBrick.hpp"

InvisibleBrick::InvisibleBrick(sf::Vector2f pos)
	: Brick(pos, frame)
{
	SetVisible(false);
}

void InvisibleBrick::Collided(GameObject* other)
{
	if (!IsVisible())
		SetVisible(true);
	else
	{
		Brick::Collided(other);
	}
}
