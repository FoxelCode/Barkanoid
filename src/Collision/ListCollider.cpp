#include "Collision/ListCollider.hpp"

void ListCollider::Draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	for each (Collider* collider in colliders)
		collider->Draw(target, states);
}

void ListCollider::AddCollider(Collider* collider)
{
	colliders.push_back(collider);
	CalculateBounds();
}

void ListCollider::Clear()
{
	colliders.clear();
	bounds = sf::FloatRect();
}

void ListCollider::RemoveCollider(Collider* collider)
{
	for (auto it = colliders.begin(); it != colliders.end(); it++)
	{
		if ((*it) == collider)
		{
			colliders.erase(it);
			CalculateBounds();
			return;
		}
	}
}

sf::FloatRect ListCollider::GetBounds()
{
	bounds.left = GetGameObject()->GetPosition().x;
	bounds.top = GetGameObject()->GetPosition().y;
	return bounds;
}

void ListCollider::CalculateBounds()
{
	sf::Vector2f min, max;
	for each (Collider* collider in colliders)
	{
		sf::FloatRect colBounds = collider->GetBounds();
		if (colBounds.left < min.x) min.x = colBounds.left;
		if (colBounds.top < min.y) min.y = colBounds.top;
		if (colBounds.left + colBounds.width > max.x) max.x = colBounds.left + colBounds.width;
		if (colBounds.top + colBounds.height > max.y) max.y = colBounds.top + colBounds.height;
	}
	bounds = sf::FloatRect(min.x, min.y, max.x - min.x, max.y - min.y);
}
