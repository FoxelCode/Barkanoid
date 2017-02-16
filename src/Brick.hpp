#pragma once

#include "GameObject.hpp"
#include "Palette.hpp"

class Brick : public GameObject
{
public:
	Brick(sf::Vector2f pos, sf::Color colour, int variant = 0);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual void Collided();

private:
	sf::Sprite highlight;
};