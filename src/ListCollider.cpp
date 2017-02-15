#include "ListCollider.hpp"

void ListCollider::RemoveCollider(Collider* collider)
{
	for (auto it = colliders.begin(); it != colliders.end(); it++)
	{
		if ((*it) == collider)
		{
			colliders.erase(it);
			return;
		}
	}
}
