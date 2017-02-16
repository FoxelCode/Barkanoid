#include "ListCollider.hpp"

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
