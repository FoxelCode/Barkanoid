#pragma once

#include "Engine/GameObject.hpp"
#include "Game/Palette.hpp"

class Brick : public GameObject
{
public:
	Brick(sf::Vector2f pos, sf::Color colour, int variant = 0);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void Collided(GameObject* other);

	static const sf::Vector2u brickSize;

private:
	sf::Sprite highlight;
};