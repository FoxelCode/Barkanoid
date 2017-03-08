#include "Collision/AABBCollider.hpp"

#include "Engine/GameObject.hpp"

sf::FloatRect AABBCollider::GetBounds()
{
	sf::Vector2f pos = GetPosition();
	return sf::FloatRect(pos.x, pos.y, getSize().x, getSize().y);
}