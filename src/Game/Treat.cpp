#include "Game/Treat.hpp"

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
	Move(velocity * delta);
}

void Treat::Separate(sf::Vector2f separation)
{
	GameObject::Separate(separation);

	separation = Math::normalise(separation);
	float VdotN = Math::dot(velocity, separation);
	velocity.x = velocity.x - 2 * VdotN * separation.x;
	velocity.y = velocity.y - 2 * VdotN * separation.y;
}
