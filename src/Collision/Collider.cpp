#include "Collision/Collider.hpp"

#include "Engine/GameObject.hpp"

sf::FloatRect Collider::GetBounds()
{
	sf::Vector2f pos = GetPosition();
	return sf::FloatRect(pos.x, pos.y, 0.0f, 0.0f);
}

sf::Vector2f Collider::GetPosition() const
{
	return GetGameObject()->GetPosition() + offset;
}
