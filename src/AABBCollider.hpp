#pragma once

#include "Collider.hpp"
#include <SFML\Graphics\RectangleShape.hpp>

class AABBCollider : public Collider, public sf::RectangleShape
{
public:
	AABBCollider(GameObject* gameObject, sf::Vector2f offset, sf::Vector2f size)
		: Collider(gameObject), sf::RectangleShape(size)
	{
		SetOffset(offset);
		setFillColor(sf::Color::Transparent);
		setOutlineThickness(-1.0f);
		setOutlineColor(sf::Color::Red);
	};

	void Draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		states.transform.translate(GetOffset());
		target.draw(*this, states);
	}

	virtual sf::FloatRect GetBounds();

	ColliderType GetType() { return ColliderType::AABB; }
};