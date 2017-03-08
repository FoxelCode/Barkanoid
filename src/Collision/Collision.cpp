#include "Collision/Collision.hpp"

#include "Engine/GameObject.hpp"
#include "Util/Math.hpp"
#include "Game/Entities/Paddle.hpp"
#include "Game/Entities/Ball.hpp"
#include "Collision/ListCollider.hpp"

sf::Vector2f Collision::Collide(Collider* a, Collider* b)
{
	sf::FloatRect aBounds = a->GetBounds();
	sf::FloatRect bBounds = b->GetBounds();
	sf::Vector2f targetLocation = a->GetGameObject()->GetPosition() + a->GetGameObject()->GetVelocity();

	// Broad phase collision
	if (!a->GetBounds().intersects(b->GetBounds()))
		return targetLocation;

	sf::Vector2f newPos = sf::Vector2f();
	if (b->GetType() == ColliderType::List)
	{
		ListCollider* bList = static_cast<ListCollider*>(b);
		for each (Collider* collider in bList->GetColliders())
		{
			newPos = Collide(a, collider);
			if (newPos != targetLocation)
				return newPos;
		}
	}

	if (a->GetType() == ColliderType::AABB && b->GetType() == ColliderType::AABB)
	{
		sf::Vector2f newPos = AABBToAABB(static_cast<AABBCollider*>(a), static_cast<AABBCollider*>(b));
		return newPos;
	}
	return targetLocation;
}

sf::Vector2f Collision::AABBToAABB(AABBCollider* a, AABBCollider* b)
{
	sf::Vector2f normal;
	float collisionTime = SweepAABB(a, b, normal);
	return a->GetGameObject()->GetPosition() + a->GetGameObject()->GetVelocity() * collisionTime;
}

float Collision::SweepAABB(AABBCollider* a, AABBCollider* b, sf::Vector2f& normal)
{
	sf::FloatRect aBounds = a->getGlobalBounds();
	aBounds.left = a->GetPosition().x;
	aBounds.top = a->GetPosition().y;
	sf::FloatRect bBounds = b->getGlobalBounds();
	bBounds.left = b->GetPosition().x;
	bBounds.top = b->GetPosition().y;
	sf::Vector2f aVel = a->GetGameObject()->GetVelocity();

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

	float entryTime = std::max(xEntry, yEntry);
	float exitTime = std::min(xExit, yExit);

	if (entryTime > exitTime || xEntry < 0.0f && yEntry < 0.0f
		|| xEntry > 1.0f || yEntry > 1.0f)
	{
		normal.x = normal.y = 0.0f;
		return 1.0f;
	}

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
