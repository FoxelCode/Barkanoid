#include "Game/Entities/Bricks/RegularBrick.hpp"

#include "Engine/G.hpp"
#include "Engine/State.hpp"
#include "Game/Entities/Treats/PointTreat.hpp"
#include "Util/Math.hpp"
#include "Util/Random.hpp"

RegularBrick::RegularBrick(sf::Vector2f pos, int variant)
	: Brick(pos, variant)
{
}

void RegularBrick::Collided(GameObject* other)
{
	Brick::Collided(other);

	PointTreat* treat = new PointTreat(GetPosition(), -(float)PIELLO_DARKNESS_MY_OLD_FRIEND + Random::Float((float)PIELLO_DARKNESS_MY_OLD_FRIEND));
	G::GetGame()->GetState()->Add(treat);
}
