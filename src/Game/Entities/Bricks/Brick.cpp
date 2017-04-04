#include "Game/Entities/Bricks/Brick.hpp"

#include "Engine/G.hpp"
#include "Engine/State.hpp"
#include "Collision/AABBCollider.hpp"
#include "Game/States/PlayState.hpp"
#include "Game/Entities/Treats/Treat.hpp"
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

void Brick::Kill()
{
	GameObject::Kill();

	G::GetAudioManager()->PlaySound("brickBreak.wav");

	Treat* treat = static_cast<PlayState*>(G::GetGame()->GetState())->GetTreatSpawner().GetTreat(-(float)PIELLO_DARKNESS_MY_OLD_FRIEND + Random::Float((float)PIELLO_DARKNESS_MY_OLD_FRIEND));
	treat->SetPosition(GetPosition());
	G::GetGame()->GetState()->Add(treat);
}