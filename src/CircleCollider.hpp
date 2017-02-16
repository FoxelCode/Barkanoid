#pragma once

#include "Collider.hpp"
#include <SFML\Graphics\CircleShape.hpp>

class CircleCollider : public Collider, public sf::CircleShape
{
public:
	CircleCollider(GameObject* gameObject, sf::Vector2f offset, float radius)
		: Collider(gameObject), sf::CircleShape(radius, 30)
	{
		SetOffset(offset);
		setFillColor(sf::Color::Transparent);
		setOutlineThickness(-1.0f);
		setOutlineColor(sf::Color::Green);
	};

	void Draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		states.transform.translate(GetOffset());
		target.draw(*this, states);
	}

	virtual sf::FloatRect GetBounds();

	ColliderType GetType() { return ColliderType::Circle; }
};