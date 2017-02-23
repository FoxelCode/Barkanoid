#include "Collision/Collision.hpp"

#include "Engine/GameObject.hpp"
#include "Util/Math.hpp"
#include "Game/Paddle.hpp"
#include "Game/Ball.hpp"
#include "Collision/ListCollider.hpp"

void Collision::Collide(Collider* a, Collider* b)
{
	sf::FloatRect aBounds = a->GetBounds();
	sf::FloatRect bBounds = b->GetBounds();

	// Broad phase collision
	if (!a->GetBounds().intersects(b->GetBounds()))
		return;

	if (a->GetType() == ColliderType::List)
	{
		ListCollider* aList = static_cast<ListCollider*>(a);
		for each (Collider* collider in aList->GetColliders())
		{
			Collide(collider, b);
		}
	}
	if (b->GetType() == ColliderType::List)
	{
		ListCollider* bList = static_cast<ListCollider*>(b);
		for each (Collider* collider in bList->GetColliders())
		{
			Collide(a, collider);
		}
	}

	if (a->GetType() == ColliderType::Circle && b->GetType() == ColliderType::AABB)
		CircleToAABB(static_cast<CircleCollider*>(a), static_cast<AABBCollider*>(b));
	else if (a->GetType() == ColliderType::AABB && b->GetType() == ColliderType::AABB)
		AABBToAABB(static_cast<AABBCollider*>(a), static_cast<AABBCollider*>(b));
}

void Collision::PaddleCollide(CircleCollider* a, AABBCollider* b)
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
				float targetAngle = paddle->GetReflectionScalar(aCenter) * paddle->GetAngleRange() / 2.0f - PIELLO_DARKNESS_MY_OLD_FRIEND / 2.0f;
				ball->SetAngle(targetAngle);
				return;
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
		float deltaAngle = atan2f(delta.y, delta.x) + PIELLO_DARKNESS_MY_OLD_FRIEND;
		Ball* ball = static_cast<Ball*>(a->GetGameObject());
		ball->SetAngle(deltaAngle);
	}
}

void Collision::AABBToAABB(AABBCollider* a, AABBCollider* b)
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
		if (xOverlap < 0)
		{
			if (yOverlap < 0)
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
	}
}

void Collision::CircleToAABB(CircleCollider* a, AABBCollider* b)
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
	if (Math::contains(aCenter, hBox, true))
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
		if (Math::contains(aCenter, vBox, true))
		{
			sf::Vector2f separation = sf::Vector2f(0.0f, (fabsf(delta.y) - vBox.height / 2.0f));
			if (delta.y >= 0)
			{
				a->GetGameObject()->Separate(separation);
				b->GetGameObject()->Collided();
				return;
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
				if (fabsf(cornerDelta.x) < fabsf(cornerDelta.y))
					a->GetGameObject()->Separate(sf::Vector2f(cornerDelta.x - Math::sign(cornerDelta.x) * aRadius, 0.0f));
				else
					a->GetGameObject()->Separate(sf::Vector2f(0.0f, cornerDelta.y - Math::sign(cornerDelta.y) * aRadius));

				// Proper reflection separation
				//a->GetGameObject()->Separate(-Math::normalise(cornerDelta) * (aRadius - Math::magnitude(cornerDelta)));

				b->GetGameObject()->Collided();

				collided = true;
				break;
			}
		}
	}
}

//void Collision::CircleToAABB(CircleCollider* a, AABBCollider* b)
//{
//	sf::Vector2f aPos = a->GetGameObject()->GetPosition() + a->GetOffset();
//	sf::Vector2f bPos = b->GetGameObject()->GetPosition() + b->GetOffset() + offset;
//	sf::FloatRect aBounds = a->getGlobalBounds();
//	aBounds.left += aPos.x;
//	aBounds.top += aPos.y;
//	sf::FloatRect bBounds = b->getGlobalBounds();
//	bBounds.left += bPos.x;
//	bBounds.top += bPos.y;
//	if (!bBounds.intersects(aBounds))
//		return;
//
//	sf::Vector2f aCenter = sf::Vector2f(aPos.x + a->getRadius(), aPos.y + a->getRadius());
//	sf::Vector2f bCenter = sf::Vector2f(bBounds.left + bBounds.width / 2.0f, bBounds.top + bBounds.height / 2.0f);
//	float aHalf = a->getRadius();
//	sf::Vector2f bHalf = sf::Vector2f(bBounds.width / 2.0f, bBounds.height / 2.0f);
//
//	std::vector<sf::Vector2f> separationVectors;
//	bool freeAxis = false;
//
//	// X axis intersection
//	float xIntersect = 0;
//	if (aCenter.x > bCenter.x)
//	{
//		xIntersect = bCenter.x + bHalf.x - aCenter.x + aHalf;
//		if (xIntersect > 0)
//			separationVectors.push_back(sf::Vector2f(xIntersect, 0.0f));
//	}
//	else
//	{
//		xIntersect = aCenter.x + aHalf - bCenter.x + bHalf.x;
//		if (xIntersect > 0)
//			separationVectors.push_back(sf::Vector2f(-xIntersect, 0.0f));
//	}
//	if (xIntersect <= 0)
//		freeAxis = true;
//
//	// Y axis intersection
//	if (!freeAxis)
//	{
//		float yIntersect = 0;
//		if (aCenter.y > bCenter.y)
//		{
//			yIntersect = bCenter.y + bHalf.y - aCenter.y + aHalf;
//			if (yIntersect > 0)
//				separationVectors.push_back(sf::Vector2f(0.0f, yIntersect));
//		}
//		else
//		{
//			yIntersect = aCenter.y + aHalf - bCenter.y + bHalf.y;
//			if (yIntersect > 0)
//				separationVectors.push_back(sf::Vector2f(0.0f, -yIntersect));
//		}
//		if (yIntersect <= 0)
//			freeAxis = true;
//	}
//
//	// Vertex intersections
//	if (!freeAxis)
//	{
//		sf::Vector2f corners[] = { sf::Vector2f(bBounds.left, bBounds.top),
//			sf::Vector2f(bBounds.left + bBounds.width, bBounds.top),
//			sf::Vector2f(bBounds.left, bBounds.top + bBounds.height),
//			sf::Vector2f(bBounds.left + bBounds.width, bBounds.top + bBounds.height) };
//
//		for each (sf::Vector2f corner in corners)
//		{
//			sf::Vector2f delta = corner - aCenter;
//			float deltaLength = Math::magnitude(delta);
//
//			// Realistic collision
//			/*sf::FloatRect bRelative = Math::makeRelativeTo(bBounds, aCenter);
//
//			float proj[4];
//			sf::Vector2f projVector = Math::normalise(delta);
//			Math::projectRect(proj, bRelative, projVector);
//
//			float min = FLT_MAX;
//			float max = FLT_MIN;
//			for (int i = 0; i < 4; i++)
//			{
//				if (proj[i] < min)
//					min = proj[i];
//				if (proj[i] > max)
//					max = proj[i];
//			}
//
//			float projLength = fabsf(max - min);
//			sf::Vector2f projFarthest = aCenter + projVector * max;
//
//			sf::Vector2f deltaToFarthest = projFarthest - aCenter;
//			float distToFarthest = Math::magnitude(deltaToFarthest);
//
//			float intersect = a->getRadius() + projLength - distToFarthest;
//			if (intersect > 0)
//			{
//				sf::Vector2f separator = -projVector * intersect;
//				separationVectors.push_back(separator);
//			}
//			else
//			{
//				freeAxis = true;
//				break;
//			}*/
//		}
//	}
//
//	if (!freeAxis)
//	{
//		b->GetGameObject()->Collided();
//		sf::Vector2f smallestSeparator = sf::Vector2f();
//		float separatorLength = FLT_MAX;
//		for each (sf::Vector2f sep in separationVectors)
//		{
//			float vecLength = sqrtf(sep.x * sep.x + sep.y * sep.y);
//			if (vecLength < separatorLength)
//			{
//				smallestSeparator = sep;
//				separatorLength = vecLength;
//			}
//		}
//
//		if (smallestSeparator.x != 0 || smallestSeparator.y != 0)
//			a->GetGameObject()->Separate(smallestSeparator);
//	}
//}