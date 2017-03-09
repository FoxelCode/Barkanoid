#include "Game/Entities/Treats/Treat.hpp"

#include "Util/Math.hpp"

Treat::Treat(sf::Vector2f pos, float launchAngle)
	: gravity(100.0f)
{
	SetPosition(pos);

	float initialVelocity = 100.0f;
	velocity.x = cosf(launchAngle) * initialVelocity;
	velocity.y = sinf(launchAngle) * initialVelocity;
}

void Treat::Update(float delta)
{
	velocity.y += gravity * delta;
	GameObject::Update(delta);
}