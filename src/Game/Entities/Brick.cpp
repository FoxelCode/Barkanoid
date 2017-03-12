#include "Game/Entities/Brick.hpp"

#include "Engine/G.hpp"
#include "Engine/State.hpp"
#include "Collision/AABBCollider.hpp"
#include "Game/Entities/Treats/PointTreat.hpp"
#include "Util/Random.hpp"
#include "Util/Math.hpp"

#include <iostream>

const sf::Vector2u Brick::brickSize = sf::Vector2u(32, 16);

Brick::Brick(sf::Vector2f pos, sf::Color colour, int variant)
	: GameObject(pos)
{
	collider = new AABBCollider(this, sf::Vector2f(), sf::Vector2f(brickSize));

	LoadGraphic(G::GetAssetManager()->GetTexture("brick_base.png"));
	graphic->SetColour(colour);
	sf::Vector2f fSize = sf::Vector2f(brickSize);
	graphic->SetFrameSize(fSize);
	graphic->SetFrame(variant);
	highlight.setTexture(*G::GetAssetManager()->GetTexture("brick_high.png"));
	highlight.setTextureRect(sf::IntRect(variant * (int)fSize.x, 0, (int)fSize.x, (int)fSize.y));
}

void Brick::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform.translate(GetPosition());
	target.draw(*graphic, states);
	target.draw(highlight, states);
}

void Brick::Collided(GameObject* other)
{
	Kill();

	PointTreat* treat = new PointTreat(GetPosition(), -(float)PIELLO_DARKNESS_MY_OLD_FRIEND + Random::Float((float)PIELLO_DARKNESS_MY_OLD_FRIEND));
	G::GetGame()->GetState()->Add(treat);
}
