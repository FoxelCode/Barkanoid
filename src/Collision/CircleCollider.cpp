#include "Collision/CircleCollider.hpp"

#include "Engine/GameObject.hpp"

sf::FloatRect CircleCollider::GetBounds()
{
	sf::Vector2f pos = GetGameObject()->GetPosition();
	return sf::FloatRect(pos.x - getRadius(), pos.y - getRadius(), getRadius() * 2.0f, getRadius() * 2.0f);
}
