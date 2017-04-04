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

	ParticleEmitter* particles = new ParticleEmitter(GetPosition(), G::GetAssetManager()->GetTexture("pointTreat.png"), 100.0f, 50.0f, 1.0f, 0.5f, 300.0f);
	particles->Emit((int)(Random::Float(10.0f) + 5.0f));
	G::GetGame()->GetState()->Add(particles);

	static_cast<PlayState*>(G::GetGame()->GetState())->AddPoints(100);

	Treat* treat = static_cast<PlayState*>(G::GetGame()->GetState())->GetTreatSpawner().GetTreat(-(float)PIELLO_DARKNESS_MY_OLD_FRIEND + Random::Float((float)PIELLO_DARKNESS_MY_OLD_FRIEND));
	if (treat != nullptr)
	{
		treat->SetPosition(GetPosition());
		G::GetGame()->GetState()->Add(treat);
	}
}