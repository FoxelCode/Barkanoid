#pragma once

#include <SFML\System\Vector2.hpp>

class Transform
{
public:
	Transform() : position() {}
	Transform(sf::Vector2f pos) : position(pos) {}

	sf::Vector2f GetPosition() const
	{
		if (parent)
			return parent->GetPosition() + position;
		return position;
	}
	void SetPosition(float x, float y) { position.x = x; position.y = y; }
	void SetPosition(sf::Vector2f p) { position = p; }
	void Move(float x, float y) { position.x += x; position.y += y; }
	void Move(sf::Vector2f v) { position += v; }

	void SetParent(Transform* parent) { this->parent = parent; }

private:
	Transform* parent = nullptr;
	sf::Vector2f position;
};