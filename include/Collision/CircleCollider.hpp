#pragma once

#include <SFML\Graphics\CircleShape.hpp>

#include "Collider.hpp"
#include "Engine/GameObject.hpp"

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
	~CircleCollider() = default;

	void Draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		states.transform.translate(GetOffset());
		if (GetGameObject())
			states.transform.translate(GetGameObject()->GetPosition());
		target.draw(*this, states);
	}

	virtual sf::FloatRect GetBounds();

	ColliderType GetType() { return ColliderType::Circle; }
};