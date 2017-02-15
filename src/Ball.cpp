#include "Ball.hpp"
#include <iostream>
#include "Math.hpp"
#include "CircleCollider.hpp"
#include "Util.hpp"

Ball::Ball(sf::Vector2f pos)
	: GameObject(pos), velocity(50.0f, -400.0f)
{
	collider = new CircleCollider(this, sf::Vector2f(-8.0f, -8.0f), 8.0f);
	SetTexture(Util::GetAssetManager()->GetTexture("ball.png"), 2.0f);
	sprite.setPosition(-8.0f, -8.0f);
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
