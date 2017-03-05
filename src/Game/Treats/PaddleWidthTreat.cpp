#include "Game/Treats/PaddleWidthTreat.hpp"

#include "Collision/AABBCollider.hpp"
#include "Engine/G.hpp"
#include "Game/PlayState.hpp"

PaddleWidthTreat::PaddleWidthTreat(sf::Vector2f pos, float launchAngle, Type type)
	: Treat(pos, launchAngle), type(type), widthChange(20.0f)
{
	float radius = 7.0f;
	collider = new AABBCollider(this, sf::Vector2f(-radius, -radius), sf::Vector2f(radius * 2.0f, radius * 2.0f));

	LoadGraphic(G::GetAssetManager()->GetTexture("pointTreat.png"));
	graphic->setPosition(sf::Vector2f(-radius, -radius));
}

void PaddleWidthTreat::AddAward(PlayState* state)
{
	if (type == Type::WidthUp)
		state->GetPaddle()->AddWidth(widthChange);
	else if (type == Type::WidthDown)
		state->GetPaddle()->AddWidth(-widthChange);
}
