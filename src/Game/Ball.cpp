#include "Game/Ball.hpp"

#include <iostream>

#include "Util/Math.hpp"
#include "Collision/CircleCollider.hpp"
#include "Engine/G.hpp"

Ball::Ball(sf::Vector2f pos)
	: GameObject(pos), velocityVec(), velocity(400.0f), angle(0.5f)
{
	collider = new CircleCollider(this, sf::Vector2f(-6.0f, -6.0f), 6.0f);

	LoadGraphic(G::GetAssetManager()->GetTexture("ball.png"));
	graphic->setPosition(-6.0f, -6.0f);

	SetAngle(angle);
}

void Ball::Update(float delta)
{
	if (moving)
		Move(velocityVec * delta);
}

void Ball::Separate(sf::Vector2f separation)
{
	GameObject::Separate(separation);

	// Shortest axis reflection
	if (fabsf(separation.y) >= fabsf(separation.x))
		velocityVec.y *= -1.0f;
	else
		velocityVec.x *= -1.0f;
	SetAngle(atan2f(velocityVec.y, velocityVec.x));
}

void Ball::SetAngle(float angle)
{
	this->angle = angle;
	sf::Vector2f dir = sf::Vector2f(cosf(angle), sinf(angle));
	velocityVec = dir * velocity;
}

void Ball::SetVelocity(float velocity)
{
	this->velocity = velocity;
	velocityVec = sf::Vector2f(cosf(angle), sinf(angle)) * velocity;
}

float Ball::GetRadius()
{
	return static_cast<CircleCollider*>(collider)->getRadius();
}
