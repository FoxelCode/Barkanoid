#pragma once

#include "Collider.hpp"
#include "AABBCollider.hpp"
#include "CircleCollider.hpp"
#include "GameObject.hpp"
#include <vector>

class ListCollider : public Collider
{
public:
	ListCollider(GameObject* gameObject)
		: Collider(gameObject) {};

	void Draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		states.transform.translate(GetOffset());
		for each (Collider* collider in colliders)
			collider->Draw(target, states);
	}
	void AddCollider(Collider* collider)
	{
		colliders.push_back(collider);
		CalculateBounds();
	}
	void RemoveCollider(Collider* collider);
	const std::vector<Collider*>& GetColliders() { return colliders; }

	ColliderType GetType() { return ColliderType::List; }
	virtual sf::FloatRect GetBounds()
	{
		bounds.left = GetGameObject()->GetPosition().x;
		bounds.top = GetGameObject()->GetPosition().y;
		return bounds;
	}
	void CalculateBounds();

private:
	std::vector<Collider*> colliders;
	sf::FloatRect bounds;
};