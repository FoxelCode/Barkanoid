#include "Game/Entities/Ball.hpp"

#include <iostream>

#include "Util/Math.hpp"
#include "Collision/AABBCollider.hpp"
#include "Engine/G.hpp"
#include "Game/Entities/Paddle.hpp"

const float Ball::SIZE = 12.0f;

Ball::Ball(sf::Vector2f pos)
	: GameObject(pos), velocityMag(400.0f), angle(0.5f)
{
	collider = new AABBCollider(this, sf::Vector2f(-Ball::SIZE / 2.0f, -Ball::SIZE / 2.0f), sf::Vector2f(Ball::SIZE, Ball::SIZE));

	LoadGraphic(G::GetAssetManager()->GetTexture("ball.png"));
	graphic->setPosition(-Ball::SIZE / 2.0f, -Ball::SIZE / 2.0f);

	SetAngle(angle);
}

void Ball::Update(float delta)
{
	if (moving)
		GameObject::Update(delta);
}

void Ball::Collided(GameObject* other, sf::Vector2f separationVelocity)
{
	if (dynamic_cast<Paddle*>(other))
	{
		SetAngle(reinterpret_cast<Paddle*>(other)->GetReflectionAngle(GetPosition()));
	}
	GameObject::Collided(other, Math::magnitude(separationVelocity) * Math::normalise(velocity));
}

void Ball::SetAngle(float angle)
{
	this->angle = angle;
	sf::Vector2f dir = sf::Vector2f(cosf(angle), sinf(angle));
	velocity = dir * velocityMag;
}

void Ball::SetVelocity(float velocity)
{
	this->velocityMag = velocity;
	this->velocity = sf::Vector2f(cosf(angle), sinf(angle)) * velocity;
}
