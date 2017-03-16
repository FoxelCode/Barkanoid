#include "Game/Entities/Bricks/Brick.hpp"

#include "Engine/G.hpp"
#include "Engine/State.hpp"
#include "Collision/AABBCollider.hpp"
#include "Game/Entities/Treats/PointTreat.hpp"
#include "Util/Random.hpp"
#include "Util/Math.hpp"

#include <iostream>

const sf::Vector2u Brick::brickSize = sf::Vector2u(32, 16);

Brick::Brick(sf::Vector2f pos, int variant)
	: GameObject(pos)
{
	collider = new AABBCollider(this, sf::Vector2f(), sf::Vector2f(brickSize));

	LoadGraphic(G::GetAssetManager()->GetTexture("brick.png"));
	graphic->SetFrameSize(sf::Vector2f(brickSize));
	graphic->SetFrame(variant);
}

void Brick::Collided(GameObject* other)
{
	Kill();
}
