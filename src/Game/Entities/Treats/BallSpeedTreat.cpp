#include "Game/Entities/Treats/BallSpeedTreat.hpp"

#include "Collision/AABBCollider.hpp"
#include "Engine/G.hpp"
#include "Game/States/PlayState.hpp"

BallSpeedTreat::BallSpeedTreat(sf::Vector2f pos, float launchAngle, Type type)
	: Treat(pos, launchAngle), type(type), speedChange(50.0f)
{
	float radius = 12.0f;
	collider = new AABBCollider(this, sf::Vector2f(-radius, -radius), sf::Vector2f(radius * 2.0f, radius * 2.0f));

	LoadGraphic(G::GetAssetManager()->GetTexture("powerup.png"));
	graphic->SetFrameSize(sf::Vector2f(24.0f, 24.0f));
	if (type == Type::SpeedDown)
		graphic->SetFrame(0);
	else
		graphic->SetFrame(1);
	graphic->setPosition(sf::Vector2f(-radius, -radius));
}

void BallSpeedTreat::AddAward(PlayState* state)
{
	if (type == Type::SpeedUp)
		state->AddBallSpeed(speedChange);
	else if (type == Type::SpeedDown)
		state->AddBallSpeed(-speedChange);
}
