#include "Game/Entities/Treats/MagneticPaddleTreat.hpp"

#include "Collision/AABBCollider.hpp"
#include "Engine/G.hpp"
#include "Game/States/PlayState.hpp"

MagneticPaddleTreat::MagneticPaddleTreat(sf::Vector2f pos, float launchAngle)
	: Treat(pos, launchAngle)
{
	float radius = 12.0f;
	collider = new AABBCollider(this, sf::Vector2f(-radius, -radius), sf::Vector2f(radius * 2.0f, radius * 2.0f));

	LoadGraphic(G::GetAssetManager()->GetTexture("powerup.png"));
	graphic->SetFrameSize(sf::Vector2f(24.0f, 24.0f));
	graphic->SetFrame(5);
	graphic->setPosition(sf::Vector2f(-radius, -radius));
}

void MagneticPaddleTreat::AddAward(PlayState* state)
{
	state->GetPaddle()->SetMagnetic(true);
}
