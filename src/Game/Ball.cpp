#include "Game/Ball.hpp"

#include <iostream>

#include "Util/Math.hpp"
#include "Collision/CircleCollider.hpp"
#include "Engine/G.hpp"

Ball::Ball(sf::Vector2f pos)
	: GameObject(pos), velocityVec(), velocity(400.0f), angle(0.5f)
{
	collider = new CircleCollider(this, sf::Vector2f(-8.0f, -8.0f), 8.0f);
	SetTexture(G::GetAssetManager()->GetTexture("ball.png"), 2.0f);
	sprite.setPosition(-8.0f, -8.0f);

	SetAngle(angle);
}

void Ball::Update(float delta)
{
	Move(delta * velocityVec.x, delta * velocityVec.y);
}

void Ball::Separate(sf::Vector2f separation)
{
	GameObject::Separate(separation);

	sf::Vector2f separationNormal = separation;
	float separationLength = sqrtf(separation.x * separation.x + separation.y * separation.y);
	separationNormal.x /= separationLength;
	separationNormal.y /= separationLength;

	float VdotN = velocityVec.x * separationNormal.x + velocityVec.y * separationNormal.y;
	velocityVec.x = velocityVec.x - 2 * VdotN * separationNormal.x;
	velocityVec.y = velocityVec.y - 2 * VdotN * separationNormal.y;
}

void Ball::SetAngle(float angle)
{
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
