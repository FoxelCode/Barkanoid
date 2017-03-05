#include "Game/Treats/PointTreat.hpp"

#include "Game/PlayState.hpp"
#include "Collision/AABBCollider.hpp"
#include "Engine/G.hpp"

PointTreat::PointTreat(sf::Vector2f pos, float launchAngle)
	: Treat(pos, launchAngle), points(100)
{
	float radius = 7.0f;
	collider = new AABBCollider(this, sf::Vector2f(-radius, -radius), sf::Vector2f(radius * 2.0f, radius * 2.0f));

	LoadGraphic(G::GetAssetManager()->GetTexture("pointTreat.png"));
	graphic->setPosition(sf::Vector2f(-radius, -radius));
}

void PointTreat::AddAward(PlayState* state)
{
	state->AddPoints(points);
}
