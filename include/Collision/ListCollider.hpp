#pragma once

#include <vector>

#include "Collider.hpp"
#include "AABBCollider.hpp"
#include "Engine/GameObject.hpp"

class ListCollider : public Collider
{
public:
	ListCollider(GameObject* gameObject)
		: Collider(gameObject) {};
	void Draw(sf::RenderTarget& target, sf::RenderStates states) const;

	void AddCollider(Collider* collider);
	void RemoveCollider(Collider* collider);
	void Clear();
	const std::vector<Collider*>& GetColliders() { return colliders; }

	ColliderType GetType() { return ColliderType::List; }
	virtual sf::FloatRect GetBounds();

private:
	/// <summary>
	/// <para>Calculates a new bounding box for this collider, using all of the child colliders.</para>
	/// </summary>
	void CalculateBounds();

	std::vector<Collider*> colliders;
	sf::FloatRect bounds;
};