#include "Brick.hpp"

#include "Util.hpp"
#include "AABBCollider.hpp"

#include <iostream>

Brick::Brick(sf::Vector2f pos, sf::Color colour)
{
	SetPosition(pos);
	collider = new AABBCollider(this, sf::Vector2f(), sf::Vector2f(32.0f, 16.0f));

	SetTexture(Util::GetAssetManager()->GetTexture("brick_base.png"), 2.0f);
	sprite.setColor(colour);
	highlight.setTexture(*Util::GetAssetManager()->GetTexture("brick_high.png"));
	highlight.setScale(textureScale, textureScale);
}

void Brick::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform.translate(GetPosition());
	target.draw(sprite, states);
	target.draw(highlight, states);

#if DRAW_COLLIDER
	if (collider)
	{
		collider->Draw(target, states);
	}
#endif
}

void Brick::Collided()
{
	Kill();
}
