#include "Game/Treats/MultiballTreat.hpp"

#include "Collision/AABBCollider.hpp"
#include "Engine/G.hpp"
#include "Game/PlayState.hpp"

MultiballTreat::MultiballTreat(sf::Vector2f pos, float launchAngle)
	: Treat(pos, launchAngle)
{
	float radius = 7.0f;
	collider = new AABBCollider(this, sf::Vector2f(-radius, -radius), sf::Vector2f(radius * 2.0f, radius * 2.0f));

	LoadGraphic(G::GetAssetManager()->GetTexture("pointTreat.png"));
	graphic->setPosition(sf::Vector2f(-radius, -radius));
}

void MultiballTreat::AddAward(PlayState* state)
{
	state->SplitBalls();
}
