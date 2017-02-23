#include "Collision/AABBCollider.hpp"

#include "Engine/GameObject.hpp"

sf::FloatRect AABBCollider::GetBounds()
{
	sf::Vector2f pos = GetGameObject()->GetPosition() + GetOffset();
	return sf::FloatRect(pos.x, pos.y, getSize().x, getSize().y);
}