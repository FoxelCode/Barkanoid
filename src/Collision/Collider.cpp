#include "Collision/Collider.hpp"

#include "Engine/GameObject.hpp"

sf::FloatRect Collider::GetBounds()
{
	sf::Vector2f pos = gameObject->GetPosition();
	return sf::FloatRect(pos.x, pos.y, 0.0f, 0.0f);
}
