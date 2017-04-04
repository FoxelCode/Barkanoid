#include "Game/Entities/Treats/PaddleWidthTreat.hpp"

#include "Collision/AABBCollider.hpp"
#include "Engine/G.hpp"
#include "Game/States/PlayState.hpp"

PaddleWidthTreat::PaddleWidthTreat(sf::Vector2f pos, float launchAngle, Type type)
	: Treat(pos, launchAngle), type(type), widthChange(20.0f)
{
	float radius = 12.0f;
	collider = new AABBCollider(this, sf::Vector2f(-radius, -radius), sf::Vector2f(radius * 2.0f, radius * 2.0f));

	LoadGraphic(G::GetAssetManager()->GetTexture("powerup.png"));
	graphic->SetFrameSize(sf::Vector2f(24.0f, 24.0f));
	if (type == Type::WidthUp)
		graphic->SetFrame(2);
	else
		graphic->SetFrame(3);
	graphic->setPosition(sf::Vector2f(-radius, -radius));
}

void PaddleWidthTreat::AddAward(PlayState* state)
{
	if (type == Type::WidthUp)
		state->GetPaddle()->AddWidth(widthChange);
	else if (type == Type::WidthDown)
		state->GetPaddle()->AddWidth(-widthChange);
}
