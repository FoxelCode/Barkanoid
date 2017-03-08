#include "Game/Entities/Ball.hpp"

#include <iostream>

#include "Util/Math.hpp"
#include "Collision/AABBCollider.hpp"
#include "Engine/G.hpp"

const float Ball::SIZE = 12.0f;

Ball::Ball(sf::Vector2f pos)
	: GameObject(pos), velocityMag(100.0f), angle(0.5f)
{
	collider = new AABBCollider(this, sf::Vector2f(-Ball::SIZE / 2.0f, -Ball::SIZE / 2.0f), sf::Vector2f(Ball::SIZE, Ball::SIZE));

	LoadGraphic(G::GetAssetManager()->GetTexture("ball.png"));
	graphic->setPosition(-Ball::SIZE / 2.0f, -Ball::SIZE / 2.0f);

	SetAngle(angle);
}

void Ball::Separate(sf::Vector2f separation)
{
	GameObject::Separate(separation);

	// Shortest axis reflection
	if (fabsf(separation.y) >= fabsf(separation.x))
		velocity.y *= -1.0f;
	else
		velocity.x *= -1.0f;
	SetAngle(atan2f(velocity.y, velocity.x));
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
