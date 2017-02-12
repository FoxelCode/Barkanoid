#include "Ball.hpp"
#include <iostream>
#include "Math.hpp"
#include "CircleCollider.hpp"

Ball::Ball(sf::Vector2f pos)
	: GameObject(), radius(10.0f), velocity(200.0f, 200.0f)
{
	SetPosition(pos);
	collider = new CircleCollider(this, sf::Vector2f(-10.0f, -10.0f), 10.0f);
	LoadTexture("ball.png");
	sprite.setPosition(-10.0f, -10.0f);
}

void Ball::Update(float delta)
{
	Move(delta * velocity.x, delta * velocity.y);
}

void Ball::Separate(sf::Vector2f separation)
{
	GameObject::Separate(separation);

	sf::Vector2f separationNormal = separation;
	float separationLength = sqrtf(separation.x * separation.x + separation.y * separation.y);
	separationNormal.x /= separationLength;
	separationNormal.y /= separationLength;

	float VdotN = velocity.x * separationNormal.x + velocity.y * separationNormal.y;
	velocity.x = velocity.x - 2 * VdotN * separationNormal.x;
	velocity.y = velocity.y - 2 * VdotN * separationNormal.y;
}

void Ball::TurnTowards(float angle)
{
	sf::Vector2f dir = sf::Vector2f(cosf(angle), sinf(angle));
	float vLength = Math::magnitude(velocity);
	velocity = dir * vLength;
}
