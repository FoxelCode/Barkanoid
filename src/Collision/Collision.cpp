#include "Collision/Collision.hpp"

#include "Engine/GameObject.hpp"
#include "Util/Math.hpp"
#include "Game/Paddle.hpp"
#include "Game/Ball.hpp"
#include "Collision/ListCollider.hpp"

bool Collision::Collide(Collider* a, Collider* b)
{
	sf::FloatRect aBounds = a->GetBounds();
	sf::FloatRect bBounds = b->GetBounds();

	// Broad phase collision
	if (!a->GetBounds().intersects(b->GetBounds()))
		return false;

	if (a->GetType() == ColliderType::List)
	{
		ListCollider* aList = static_cast<ListCollider*>(a);
		for each (Collider* collider in aList->GetColliders())
		{
			if (Collide(collider, b))
				return true;
		}
	}
	if (b->GetType() == ColliderType::List)
	{
		ListCollider* bList = static_cast<ListCollider*>(b);
		for each (Collider* collider in bList->GetColliders())
		{
			if (Collide(a, collider))
				return true;
		}
	}

	if (a->GetType() == ColliderType::Circle && b->GetType() == ColliderType::AABB)
	{
		if (CircleToAABB(static_cast<CircleCollider*>(a), static_cast<AABBCollider*>(b)))
			return true;
	}
	else if (a->GetType() == ColliderType::AABB && b->GetType() == ColliderType::AABB)
	{
		if (AABBToAABB(static_cast<AABBCollider*>(a), static_cast<AABBCollider*>(b)))
			return true;
	}
	return false;
}

bool Collision::PaddleCollide(CircleCollider* a, AABBCollider* b)
{
	float aRadius = a->getRadius();
	sf::Vector2f aCenter = a->GetGameObject()->GetPosition();
	sf::FloatRect bBounds = b->getGlobalBounds();
	bBounds.left = b->GetGameObject()->GetPosition().x + b->GetOffset().x;
	bBounds.top = b->GetGameObject()->GetPosition().y + b->GetOffset().y;

	sf::FloatRect hBox = bBounds;
	sf::Vector2f bCenter = sf::Vector2f(hBox.left + hBox.width / 2.0f, hBox.top + hBox.height / 2.0f);
	hBox.left -= aRadius;
	hBox.width += aRadius * 2;
	sf::FloatRect vBox = bBounds;
	vBox.top -= aRadius;
	vBox.height += aRadius * 2;

	sf::Vector2f delta = bCenter - aCenter;
	bool collided = false;

	// Horizontal collision with AABB
	if (Math::contains(aCenter, hBox, false))
	{
		sf::Vector2f separation = sf::Vector2f((fabsf(delta.x) - hBox.width / 2.0f), 0.0f);
		if (delta.x >= 0)
			a->GetGameObject()->Separate(separation);
		else
			a->GetGameObject()->Separate(-separation);
		b->GetGameObject()->Collided();
		collided = true;
	}

	if (!collided)
	{
		// Vertical collision with AABB
		if (Math::contains(aCenter, vBox, false))
		{
			sf::Vector2f separation = sf::Vector2f(0.0f, (fabsf(delta.y) - vBox.height / 2.0f));
			if (delta.y >= 0)
			{
				a->GetGameObject()->Separate(separation);
				b->GetGameObject()->Collided();
				Paddle* paddle = static_cast<Paddle*>(b->GetGameObject());
				Ball* ball = static_cast<Ball*>(a->GetGameObject());
				float targetAngle = paddle->GetReflectionScalar(aCenter) * paddle->GetAngleRange() / 2.0f - (float)PIELLO_DARKNESS_MY_OLD_FRIEND / 2.0f;
				ball->SetAngle(targetAngle);
				return true;
			}
			else
			{
				a->GetGameObject()->Separate(-separation);
				b->GetGameObject()->Collided();
			}
			collided = true;
		}
	}

	if (!collided)
	{
		// Corner collision
		sf::Vector2f corners[] = { sf::Vector2f(bBounds.left, bBounds.top),
			sf::Vector2f(bBounds.left + bBounds.width, bBounds.top),
			sf::Vector2f(bBounds.left, bBounds.top + bBounds.height),
			sf::Vector2f(bBounds.left + bBounds.width, bBounds.top + bBounds.height) };

		for each (sf::Vector2f corner in corners)
		{
			sf::Vector2f cornerDelta = corner - aCenter;
			if (Math::magnitude(cornerDelta) < aRadius)
			{
				// Smallest axis separation
				/*if (fabsf(cornerDelta.x) < fabsf(cornerDelta.y))
				a->Separate(sf::Vector2f(cornerDelta.x - Math::sign(cornerDelta.x) * aRadius, 0.0f));
				else
				a->Separate(sf::Vector2f(0.0f, cornerDelta.y - Math::sign(cornerDelta.y) * aRadius));*/

				// Proper reflection separation
				a->GetGameObject()->Separate(-Math::normalise(cornerDelta) * (aRadius - Math::magnitude(cornerDelta)));
				b->GetGameObject()->Collided();

				collided = true;
				break;
			}
		}
	}

	if (collided)
	{
		float deltaAngle = atan2f(delta.y, delta.x) + (float)PIELLO_DARKNESS_MY_OLD_FRIEND;
		Ball* ball = static_cast<Ball*>(a->GetGameObject());
		ball->SetAngle(deltaAngle);
	}
	return collided;
}

bool Collision::AABBToAABB(AABBCollider* a, AABBCollider* b)
{
	sf::FloatRect aBounds = a->getGlobalBounds();
	aBounds.left = a->GetGameObject()->GetPosition().x + a->GetOffset().x;
	aBounds.top = a->GetGameObject()->GetPosition().y + a->GetOffset().y;
	sf::FloatRect bBounds = b->getGlobalBounds();
	bBounds.left = b->GetGameObject()->GetPosition().x + b->GetOffset().x;
	bBounds.top = b->GetGameObject()->GetPosition().y + b->GetOffset().y;

	if (aBounds.intersects(bBounds))
	{
		sf::Vector2f aCenter = sf::Vector2f(aBounds.left + aBounds.width / 2.0f, aBounds.top + aBounds.height / 2.0f);
		sf::Vector2f bCenter = sf::Vector2f(bBounds.left + bBounds.width / 2.0f, bBounds.top + bBounds.height / 2.0f);
		float xOverlap = fabsf(bCenter.x - aCenter.x) - aBounds.width / 2.0f - bBounds.width / 2.0f;
		float yOverlap = fabsf(bCenter.y - aCenter.y) - aBounds.height / 2.0f - bBounds.height / 2.0f;
		if (xOverlap < 0.0f)
		{
			if (yOverlap < 0.0f)
			{
				if (xOverlap > yOverlap)
					a->GetGameObject()->Separate(sf::Vector2f(xOverlap * Math::sign(bCenter.x - aCenter.x), 0.0f));
				else
					a->GetGameObject()->Separate(sf::Vector2f(yOverlap * Math::sign(bCenter.y - aCenter.y), 0.0f));
			}
			else
				a->GetGameObject()->Separate(sf::Vector2f(xOverlap * Math::sign(bCenter.x - aCenter.x), 0.0f));
		}
		else
			a->GetGameObject()->Separate(sf::Vector2f(yOverlap * Math::sign(bCenter.y - aCenter.y), 0.0f));
		b->GetGameObject()->Collided();
		return true;
	}
	return false;
}

bool Collision::CircleToAABB(CircleCollider* a, AABBCollider* b)
{
	float aRadius = a->getRadius();
	sf::Vector2f aCenter = a->GetGameObject()->GetPosition();
	sf::FloatRect bBounds = b->getGlobalBounds();
	bBounds.left = b->GetGameObject()->GetPosition().x + b->GetOffset().x;
	bBounds.top = b->GetGameObject()->GetPosition().y + b->GetOffset().y;
	sf::FloatRect hBox = bBounds;
	sf::Vector2f bCenter = sf::Vector2f(hBox.left + hBox.width / 2.0f, hBox.top + hBox.height / 2.0f);
	hBox.left -= aRadius;
	hBox.width += aRadius * 2;
	sf::FloatRect vBox = bBounds;
	vBox.top -= aRadius;
	vBox.height += aRadius * 2;
	sf::Vector2f delta = bCenter - aCenter;
	bool collided = false;

	float hSeparation = 0.0f;
	float vSeparation = 0.0f;
	sf::Vector2f cornerSeparation = sf::Vector2f();

	// Horizontal collision with AABB
	if (Math::contains(aCenter, hBox, true))
	{
		hSeparation = fabsf(delta.x) - hBox.width / 2.0f;
		if (delta.x < 0)
			hSeparation = -hSeparation;
		collided = true;
	}

	// Vertical collision with AABB
	if (Math::contains(aCenter, vBox, true))
	{
		vSeparation = fabsf(delta.y) - vBox.height / 2.0f;
		if (delta.y < 0)
			vSeparation = -vSeparation;
		collided = true;
	}

	// Corner collision
	sf::Vector2f corners[] = { sf::Vector2f(bBounds.left, bBounds.top),
		sf::Vector2f(bBounds.left + bBounds.width, bBounds.top),
		sf::Vector2f(bBounds.left, bBounds.top + bBounds.height),
		sf::Vector2f(bBounds.left + bBounds.width, bBounds.top + bBounds.height) };

	for each (sf::Vector2f corner in corners)
	{
		sf::Vector2f cornerDelta = corner - aCenter;
		if (Math::magnitude(cornerDelta) < aRadius)
		{
			// Smallest axis separation
			/*if (fabsf(cornerDelta.x) < fabsf(cornerDelta.y))
			{
				hSeparation = cornerDelta.x - Math::sign(cornerDelta.x) * aRadius;
				vSeparation = 0.0f;
			}
			else
			{
				vSeparation = cornerDelta.y - Math::sign(cornerDelta.y) * aRadius;
				hSeparation = 0.0f;
			}*/

			// Proper reflection separation
			cornerSeparation = -Math::normalise(cornerDelta) * (aRadius - Math::magnitude(cornerDelta));

			collided = true;
			break;
		}
	}

	// Separate collider A from collider B
	if (collided)
	{
		if (cornerSeparation.x != 0.0f || cornerSeparation.y != 0.0f)
		{
			// Separate from a corner (it should always be the smallest separator if it's set)
			a->GetGameObject()->Separate(cornerSeparation);
		}
		else
		{
			// Separate either along the horizontal or the vertical axis
			if (hSeparation != 0.0f)
			{
				if (vSeparation != 0.0f)
				{
					if (fabsf(hSeparation) < fabsf(vSeparation))
						a->GetGameObject()->Separate(sf::Vector2f(hSeparation, 0.0f));
					else
						a->GetGameObject()->Separate(sf::Vector2f(0.0f, vSeparation));
				}
				else
					a->GetGameObject()->Separate(sf::Vector2f(hSeparation, 0.0f));
			}
			else if (vSeparation != 0.0f)
				a->GetGameObject()->Separate(sf::Vector2f(0.0f, vSeparation));
		}

		// Notify the other collider's GameObject that we collided
		b->GetGameObject()->Collided();
	}

	return collided;
}