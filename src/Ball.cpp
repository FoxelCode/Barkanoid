#include "Ball.hpp"
#include <iostream>
#include "Math.hpp"

Ball::Ball(sf::Vector2f pos)
	: sf::CircleShape(20.0f, 30), radius(20.0f), velocity(200.0f, 160.0f)
{
	setPosition(sf::Vector2f(pos.x - radius, pos.y - radius));
	sf::CircleShape::setFillColor(sf::Color(0, 255, 255));
}

void Ball::Update(float delta)
{
	sf::Vector2f oldPos = getPosition();
	setPosition(oldPos.x + delta * velocity.x, oldPos.y + delta * velocity.y);
}

void Ball::Separate(sf::Vector2f separation)
{
	move(separation);

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
	sf::Vector2f dir = sf::Vector2f(sinf(angle), cosf(angle));
	float vLength = Math::magnitude(velocity);
	velocity = dir * vLength;
}
