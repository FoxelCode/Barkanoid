#include "Collision/Collision.hpp"

#include "Engine/GameObject.hpp"
#include "Util/Math.hpp"
#include "Game/Entities/Paddle.hpp"
#include "Game/Entities/Ball.hpp"
#include "Collision/ListCollider.hpp"

float Collision::delta = 1.0f;

bool Collision::Collide(Collider* a, Collider* b)
{
	if (b->GetType() == ColliderType::List)
	{
		ListCollider* bList = static_cast<ListCollider*>(b);
		for each (Collider* collider in bList->GetColliders())
		{
			if (Collide(a, collider))
				return true;
		}
	}

	if (a->GetType() == ColliderType::AABB && b->GetType() == ColliderType::AABB)
	{
		return AABBToAABB(static_cast<AABBCollider*>(a), static_cast<AABBCollider*>(b));
	}
	return false;
}

bool Collision::AABBToAABB(AABBCollider* a, AABBCollider* b)
{
	// Broadphase
	sf::FloatRect broadphaseRect = GetSweepBroadphaseRect(a);
	if (!broadphaseRect.intersects(b->GetBounds()))
		return false;

	// Sweep collision
	sf::Vector2f normal;
	float collisionTime = SweepAABB(a, b, normal);

	// Sweep didn't find a collision
	if (collisionTime >= 1.0f)
		return false;

	// Collision response ( reflection )

	// Set new velocity after reflection
	sf::Vector2f newVelocity = a->GetGameObject()->GetVelocity();
	if (fabsf(normal.x) > 0.00001f)
		newVelocity.x *= -1;
	if (fabsf(normal.y) > 0.00001f)
		newVelocity.y *= -1;
	a->GetGameObject()->SetVelocity(newVelocity);

	// Use remaining velocity to reflect
	float remainingTime = 1.0 - collisionTime;
	sf::Vector2f reflection = newVelocity * delta * remainingTime;

	// Notify both objects of the collision
	a->GetGameObject()->Collided(b->GetGameObject(), reflection);
	b->GetGameObject()->Collided(a->GetGameObject());

	return true;
}

sf::FloatRect Collision::GetSweepBroadphaseRect(AABBCollider* a)
{
	sf::FloatRect bounds = a->getGlobalBounds();
	bounds.left = a->GetPosition().x;
	bounds.top = a->GetPosition().y;
	sf::Vector2f vel = a->GetGameObject()->GetVelocity() * delta;

	sf::FloatRect rect;
	rect.left = (vel.x > 0) ? bounds.left : bounds.left + vel.x;
	rect.top = (vel.y > 0) ? bounds.top : bounds.top + vel.y;
	rect.width = (vel.x > 0) ? vel.x + bounds.width : bounds.width - vel.x;
	rect.height = (vel.y > 0) ? vel.y + bounds.height : bounds.height - vel.y;
	return rect;
}

float Collision::SweepAABB(AABBCollider* a, AABBCollider* b, sf::Vector2f& normal)
{
	sf::FloatRect aBounds = a->getGlobalBounds();
	aBounds.left = a->GetPosition().x;
	aBounds.top = a->GetPosition().y;
	sf::FloatRect bBounds = b->getGlobalBounds();
	bBounds.left = b->GetPosition().x;
	bBounds.top = b->GetPosition().y;
	sf::Vector2f aVel = a->GetGameObject()->GetVelocity() * delta;

	// Calculate entry and exit distances for both axes
	float xInvEntry, yInvEntry;
	float xInvExit, yInvExit;

	if (aVel.x > 0.0f)
	{
		xInvEntry = bBounds.left - (aBounds.left + aBounds.width);
		xInvExit = (bBounds.left + bBounds.width) - aBounds.left;
	}
	else
	{
		xInvEntry = (bBounds.left + bBounds.width) - aBounds.left;
		xInvExit = bBounds.left - (aBounds.left + aBounds.width);
	}

	if (aVel.y > 0.0f)
	{
		yInvEntry = bBounds.top - (aBounds.top + aBounds.height);
		yInvExit = (bBounds.top + bBounds.height) - aBounds.top;
	}
	else
	{
		yInvEntry = (bBounds.top + bBounds.height) - aBounds.top;
		yInvExit = bBounds.top - (aBounds.top + aBounds.height);
	}

	// Calculate entry and exit times for both axes
	float xEntry, yEntry;
	float xExit, yExit;

	if (aVel.x == 0.0f)
	{
		xEntry = -std::numeric_limits<float>::infinity();
		xExit = std::numeric_limits<float>::infinity();
	}
	else
	{
		xEntry = xInvEntry / aVel.x;
		xExit = xInvExit / aVel.x;
	}

	if (aVel.y == 0.0f)
	{
		yEntry = -std::numeric_limits<float>::infinity();
		yExit = std::numeric_limits<float>::infinity();
	}
	else
	{
		yEntry = yInvEntry / aVel.y;
		yExit = yInvExit / aVel.y;
	}

	// Find the latest entry time and earliest exit time
	float entryTime = std::max(xEntry, yEntry);
	float exitTime = std::min(xExit, yExit);

	// Check if there was no collision
	if (entryTime > exitTime || xEntry < 0.0f && yEntry < 0.0f
		|| xEntry > 1.0f || yEntry > 1.0f)
	{
		normal.x = normal.y = 0.0f;
		return 1.0f;
	}

	// There was a collision, set the separation normal
	if (xEntry > yEntry)
	{
		if (xInvEntry < 0.0f)
		{
			normal.x = 1.0f;
			normal.y = 0.0f;
		}
		else
		{
			normal.x = -1.0f;
			normal.y = 0.0f;
		}
	}
	else
	{
		if (yInvEntry < 0.0f)
		{
			normal.x = 0.0f;
			normal.y = 1.0f;
		}
		else
		{
			normal.x = 0.0f;
			normal.y = -1.0f;
		}
	}
	return entryTime;
}
