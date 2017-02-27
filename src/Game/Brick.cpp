#include "Game/Brick.hpp"

#include "Engine/G.hpp"
#include "Collision/AABBCollider.hpp"

#include <iostream>

Brick::Brick(sf::Vector2f pos, sf::Color colour, int variant)
	: GameObject(pos)
{
	collider = new AABBCollider(this, sf::Vector2f(), sf::Vector2f(32.0f, 16.0f));

	LoadGraphic(G::GetAssetManager()->GetTexture("brick_base.png"));
	graphic->SetColour(colour);
	sf::Vector2f fSize = sf::Vector2f(32, 16);
	graphic->SetFrameSize(fSize);
	graphic->SetFrame(variant);
	highlight.setTexture(*G::GetAssetManager()->GetTexture("brick_high.png"));
	highlight.setTextureRect(sf::IntRect(variant * fSize.x, 0, fSize.x, fSize.y));
}

void Brick::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform.translate(GetPosition());
	target.draw(*graphic, states);
	target.draw(highlight, states);
}

void Brick::Collided()
{
	Kill();
}