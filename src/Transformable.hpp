#pragma once

#include <SFML\System\Vector2.hpp>

class Transformable
{
public:
	Transformable() : position() {}
	Transformable(sf::Vector2f pos) : position(pos) {}

	sf::Vector2f GetPosition() const { return position; }
	void SetPosition(float x, float y) { position.x = x; position.y = y; }
	void SetPosition(sf::Vector2f p) { position = p; }
	void Move(float x, float y) { position.x += x; position.y += y; }
	void Move(sf::Vector2f v) { position += v; }

private:
	sf::Vector2f position;
};