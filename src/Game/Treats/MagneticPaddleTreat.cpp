#include "Game/Treats/MagneticPaddleTreat.hpp"

#include "Collision/AABBCollider.hpp"
#include "Engine/G.hpp"
#include "Game/PlayState.hpp"

MagneticPaddleTreat::MagneticPaddleTreat(sf::Vector2f pos, float launchAngle)
	: Treat(pos, launchAngle)
{
	float radius = 7.0f;
	collider = new AABBCollider(this, sf::Vector2f(-radius, -radius), sf::Vector2f(radius * 2.0f, radius * 2.0f));

	LoadGraphic(G::GetAssetManager()->GetTexture("pointTreat.png"));
	graphic->setPosition(sf::Vector2f(-radius, -radius));
}

void MagneticPaddleTreat::AddAward(PlayState* state)
{
	state->GetPaddle()->SetMagnetic(true);
}
